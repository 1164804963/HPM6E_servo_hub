import gzip
import hashlib
import json
import pathlib
import shutil

root = pathlib.Path(r"D:/Documents/SoftwareProject/YeeZi_HPM6E/MyProject/HPM6E_servo_hub_dsh")
src = pathlib.Path(r"D:/Documents/ChatGPT/YeeZi")
out = root / "doc/validation/2026-11-07/dma_timing"
datasets = ["first", "confirm", "priority", "o2", "coherent"]


def sha256(path):
    return hashlib.sha256(pathlib.Path(path).read_bytes()).hexdigest()


def copy(src_path, dst_path):
    dst_path.parent.mkdir(parents=True, exist_ok=True)
    shutil.copy2(src_path, dst_path)


manifest = {
    "source_root": str(src),
    "datasets": {},
    "files": {},
    "notes": {
        "raw_compression": "gzip.compress(..., mtime=0); lossless",
        "final_restored": "not archived: Codex reported it was still being generated",
        "original_4mb_backup": str(root / "adc_ab_backup/flash_part0.bin"),
    },
}

total_rows = 0
for ds in datasets:
    raw = src / "dma_measurements" / ds / "raw_console.json"
    raw_bytes = raw.read_bytes()
    raw_doc = json.loads(raw_bytes.decode("utf-8"))
    captures = raw_doc.get("captures", [])
    rows = sum(len(c.get("rows", [])) for c in captures)
    total_rows += rows
    gz_data = gzip.compress(raw_bytes, mtime=0)
    gz_path = out / "data" / "raw" / ds / "raw_console.json.gz"
    gz_path.parent.mkdir(parents=True, exist_ok=True)
    gz_path.write_bytes(gz_data)
    analysis_src = src / "dma_measurements" / ds / "analysis.json"
    analysis_dst = out / "data" / "analysis" / ds / "analysis.json"
    copy(analysis_src, analysis_dst)
    manifest["datasets"][ds] = {
        "captures": len(captures),
        "rows": rows,
        "raw_original": str(raw),
        "raw_original_sha256": hashlib.sha256(raw_bytes).hexdigest(),
        "raw_gzip": str(gz_path),
        "raw_gzip_sha256": hashlib.sha256(gz_data).hexdigest(),
        "analysis": str(analysis_dst),
        "analysis_sha256": sha256(analysis_dst),
    }

for name in [
    "dma_speed_baseline.json",
    "dma_speed_lowkp_aborted_graph.json",
    "dma_speed_lowkp.json",
    "dma_speed_gain.json",
    "dma_speed_o2_gain.json",
    "dma_speed_coherent_gain.json",
]:
    copy(src / name, out / "data" / "speed" / name)
    manifest["files"][f"speed/{name}"] = sha256(out / "data" / "speed" / name)

for name, folder in [
    ("dma_current_regression.json", "current"),
    ("dma_original_packets.json", "state"),
    ("dma_before_coherent_state.json", "state"),
]:
    copy(src / name, out / "data" / folder / name)
    manifest["files"][f"{folder}/{name}"] = sha256(out / "data" / folder / name)

copy(src / "dma_measurements" / "flash_coherent.log", out / "data" / "logs" / "flash_coherent.log")
manifest["files"]["logs/flash_coherent.log"] = sha256(out / "data" / "logs" / "flash_coherent.log")

for name in ["DMA_CAPTURE_RESULT.md", "DMA_TIMING_RESULT.md",
             "DMA_PRIORITY_RESULT.md", "DMA_O2_RESULT.md",
             "DMA_COHERENT_RESULT.md", "dma_boundary_check.log"]:
    copy(root / "build-hpm6e80/diagnosis" / name, out / "build_evidence" / name)

for name, dst in [
    ("dma_priority/board_priority.patch", "patches/board_priority.patch"),
    ("dma_priority/servo_console_adcinfo.patch", "patches/servo_console_adcinfo.patch"),
    ("dma_o2/source_git_diff.patch", "patches/source_git_diff_o2.patch"),
    ("dma_coherent/source_coherent.patch", "patches/source_coherent.patch"),
    ("dma_priority/manifest.txt", "manifests/dma_priority_manifest.txt"),
    ("dma_o2/manifest.json", "manifests/dma_o2_manifest.json"),
    ("dma_coherent/manifest.json", "manifests/dma_coherent_manifest.json"),
]:
    copy(root / "build-hpm6e80/diagnosis" / name, out / dst)

manifest["totals"] = {"datasets": len(datasets), "captures": 18, "rows": total_rows}
manifest["build_evidence"] = [
    "DMA_CAPTURE_RESULT.md", "DMA_TIMING_RESULT.md",
    "DMA_PRIORITY_RESULT.md", "DMA_O2_RESULT.md",
    "DMA_COHERENT_RESULT.md", "dma_boundary_check.log",
]
manifest["patches"] = [
    "patches/board_priority.patch", "patches/servo_console_adcinfo.patch",
    "patches/source_git_diff_o2.patch", "patches/source_coherent.patch",
]
(out / "data" / "manifest.json").write_text(
    json.dumps(manifest, ensure_ascii=False, indent=2), encoding="utf-8"
)
print(json.dumps(manifest["totals"], indent=2))
print(json.dumps({k: {"captures": v["captures"], "rows": v["rows"]}
                  for k, v in manifest["datasets"].items()}, indent=2))
