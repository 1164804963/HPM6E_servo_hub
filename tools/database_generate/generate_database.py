"""Regenerate the HPM6E80 database with the legacy Windows generator."""
import argparse
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys
import tempfile

MENUS = (
    ("CiA402", b"3\n0\n"),
    ("APP parameters", b"1\n3\n0\n0\n"),
    ("Flash parameters", b"1\n4\n0\n0\n"),
    ("CANopen EDS and SlaveOD", b"5\n0\n"),
    ("EtherCAT callbacks", b"4\n2\n0\n0\n"),
)
CIA402 = "communication/callback/cia402_od"
SLAVE_OD = "communication/protocol/CANopen/SlaveOD"
ECAT_CALLBACK = "communication/callback/ethercat/ecat_callback.c"
EDS = f"{SLAVE_OD}/SlaveOD.eds"
OUTPUTS = (
    f"{CIA402}/Cia402_ObjectDictionary_Callback.c",
    f"{CIA402}/Cia402_ObjectDictionary_Callback.h",
    f"{CIA402}/Cia402_ObjectDictionary_Variable.c",
    f"{CIA402}/Cia402_ObjectDictionary_Variable.h",
    f"{CIA402}/master_cia402_callback.c",
    "database/data_param.c",
    "database/data_param.h",
    "app/app_store_param.c",
    "app/app_store_param.h",
    f"{SLAVE_OD}/SlaveOD.c",
    f"{SLAVE_OD}/SlaveOD.h",
    EDS,
    ECAT_CALLBACK,
)
GENERATOR_DIR = "tools/database_generate"
INPUTS = (
    "code_generate_tool.exe", "gen_canopen_protocol_code.exe",
    "Cia402_ObjectDictionary_all.csv", "servo_hub_database_all.csv",
    "enums.csv", "mav_cmd.csv", "template.eds",
)
GENERATOR_SOURCE_DIRS = (
    "app", "database", CIA402, "communication/callback/ethercat",
    "communication/callback/mavlink", SLAVE_OD,
    "communication/protocol/EtherCAT_LAN925x", "common/software_scope",
    "communication/protocol/MAVLink/servo_hub_database",
)
SOURCE_DIRS = (
    "app", "board_public", "boards", "cmake", "common", "communication",
    "database", "embedded_project/HPM6E80", "motor_control", "simulink_code_gen",
)


def run_generator(directory, label, commands):
    with tempfile.TemporaryFile() as log:
        with subprocess.Popen(
            [str(directory / INPUTS[0])], cwd=directory,
            stdin=subprocess.PIPE, stdout=log, stderr=subprocess.STDOUT,
            env={**os.environ, "PYTHONIOENCODING": "utf-8"},
        ) as process:
            try:
                process.communicate(commands, timeout=60)
            except subprocess.TimeoutExpired:
                subprocess.run(["taskkill", "/PID", str(process.pid), "/T", "/F"],
                               stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL, check=False)
                process.kill()
                process.wait()
                log.seek(max(0, log.tell() - 3000))
                details = log.read().decode("gb18030", errors="replace")
                raise RuntimeError(f"{label}: generator timed out\n{details}") from None
            if process.returncode != 0:
                log.seek(max(0, log.tell() - 4000))
                details = log.read().decode("gb18030", errors="replace")
                raise RuntimeError(f"{label}: generator exited with {process.returncode}\n{details}")


def normalize_eds(generated, current):
    # These fields contain the wall-clock time from the old generator.
    for key in (b"CreationDate", b"CreationTime", b"ModificationDate", b"ModificationTime"):
        field = rb"(?m)^" + key + rb"=[^\n]*$"
        previous = re.findall(field, current)
        if len(previous) != 1 or len(re.findall(field, generated)) != 1:
            raise RuntimeError(f"Unexpected EDS field: {key.decode()}")
        generated = re.sub(field, lambda _: previous[0], generated)
    return generated


def generate(root, work, original):
    directory = work / GENERATOR_DIR
    directory.mkdir(parents=True)
    for name in INPUTS:
        shutil.copyfile(root / GENERATOR_DIR / name, directory / name)

    for name in GENERATOR_SOURCE_DIRS:
        shutil.copytree(root / name, work / name)

    # The generator extracts USER CODE from these files and rewrites them in place.
    for name, data in original.items():
        path = work / name
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(data)
        os.utime(path, (1, 1))
    for label, commands in MENUS:
        run_generator(directory, label, commands)
    for name in OUTPUTS:
        path = work / name
        if path.stat().st_mtime <= 1:
            raise RuntimeError(f"Generator did not write {name}")
        data = path.read_bytes().replace(b"\r\n", b"\n")
        path.write_bytes(normalize_eds(data, original[name]) if name == EDS else data)

    patch = Path(__file__).with_name("hpm6e80-generated.patch").resolve()
    command = ["git", "-c", "core.autocrlf=false", "-c", "core.eol=lf",
               "apply", "--whitespace=nowarn"]
    subprocess.run([*command, "--check", str(patch)], cwd=work, check=True)
    subprocess.run([*command, str(patch)], cwd=work, check=True)
    result = {}
    for name in OUTPUTS:
        data = (work / name).read_bytes().replace(b"\r\n", b"\n")
        result[name] = original[name] if data == original[name].replace(b"\r\n", b"\n") else data

    # A newly generated write callback must propagate EtherCAT SDO errors as well.
    ecat = result[ECAT_CALLBACK].replace(b"\r\n", b"\n")
    callbacks = re.findall(rb"(?m)^UINT8 EtherCAT_Write_\w+_Callback\([^\n]+\)\{\n(.*?)^\}",
                           ecat, flags=re.DOTALL)
    named_callbacks = re.findall(rb"(?m)^UINT8 EtherCAT_Write_\w+_Callback\(", ecat)
    if not callbacks or len(callbacks) != len(named_callbacks) or any(
            not body.lstrip().startswith(b"return ethercat_write_od(") for body in callbacks):
        raise RuntimeError("A generated EtherCAT write callback lacks the SDO abort mapping")
    return result


def verify_builds(root, candidate, generated):
    for name in SOURCE_DIRS:
        shutil.copytree(root / name, candidate / name, ignore=shutil.ignore_patterns("build*"))
    (candidate / ".vscode").mkdir()
    shutil.copyfile(root / ".vscode/settings.json", candidate / ".vscode/settings.json")
    (candidate / "tools").mkdir()
    build = candidate / "tools/build_hpm6e80.ps1"
    shutil.copyfile(root / "tools/build_hpm6e80.ps1", build)
    for name, data in generated.items():
        (candidate / name).write_bytes(data)
    shell = shutil.which("pwsh") or shutil.which("powershell")
    if not shell:
        raise RuntimeError("PowerShell is required to verify generated sources")
    for bus in ("ETHERCAT", "CAN_CIA402", "CANOPEN_CIA402"):
        subprocess.run([shell, "-NoProfile", "-File", str(build), "-Bus", bus], check=True)


def publish(root, original, changed, inputs):
    if any((root / name).read_bytes() != data for name, data in original.items()) or any(
            (root / GENERATOR_DIR / name).read_bytes() != data for name, data in inputs.items()):
        raise RuntimeError("Sources or generator inputs changed during verification. Regenerate again.")
    written = []
    with tempfile.TemporaryDirectory(prefix=".database-update-", dir=root) as staging:
        staging = Path(staging)
        for index, (name, data) in enumerate(changed.items()):
            (staging / f"{index}.new").write_bytes(data)
            (staging / f"{index}.old").write_bytes(original[name])
        try:
            for index, name in enumerate(changed):
                (staging / f"{index}.new").replace(root / name)
                written.append((index, name))
        except OSError:
            for index, name in reversed(written):
                (staging / f"{index}.old").replace(root / name)
            raise


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=Path, default=Path(__file__).resolve().parents[2],
                        help="HPM6E80 project root")
    mode = parser.add_mutually_exclusive_group()
    mode.add_argument("--output", type=Path, help="export generated files to a new directory for review")
    mode.add_argument("--apply", action="store_true", help="build three configurations, then update source files")
    args = parser.parse_args()
    root = args.root.resolve()
    if args.output and args.output.exists():
        parser.error("--output must be a new directory")
    original = {name: (root / name).read_bytes() for name in OUTPUTS}
    inputs = {name: (root / GENERATOR_DIR / name).read_bytes() for name in INPUTS}

    with tempfile.TemporaryDirectory(prefix="servo-db-") as temporary:
        temporary = Path(temporary)
        generated = generate(root, temporary / "generate", original)
        changed = {name: data for name, data in generated.items() if data != original[name]}
        print(f"{len(OUTPUTS)} files generated, {len(changed)} changed", flush=True)
        for name in changed:
            print(f"  {name}", flush=True)
        if args.output:
            args.output.mkdir(parents=True)
            for name, data in generated.items():
                path = args.output / name
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_bytes(data)
        if args.apply and changed:
            verify_builds(root, temporary / "build", generated)
            publish(root, original, changed, inputs)
            print(f"Updated {len(changed)} generated files")


if __name__ == "__main__":
    try:
        main()
    except (OSError, RuntimeError, subprocess.CalledProcessError) as exc:
        sys.exit(f"Generation failed: {exc}")
