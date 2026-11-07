import gzip
import json
import sys
from pathlib import Path

PLOT_LIBS = Path(r"D:/Documents/ChatGPT/YeeZi/filter-study/plot-libs")
sys.path.insert(0, str(PLOT_LIBS))

import numpy as np
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib import font_manager

ROOT = Path(r"D:/Documents/SoftwareProject/YeeZi_HPM6E/MyProject/HPM6E_servo_hub_dsh")
BASE = ROOT / "doc/validation/2026-11-07/dma_timing"
SRC = Path(r"D:/Documents/ChatGPT/YeeZi")
FIG = BASE / "figures"
FIG.mkdir(parents=True, exist_ok=True)

font_path = Path(r"C:/Windows/Fonts/msyh.ttc")
if font_path.exists():
    font_manager.fontManager.addfont(str(font_path))
plt.rcParams["font.family"] = "Microsoft YaHei"
plt.rcParams["axes.unicode_minus"] = False
plt.rcParams["figure.dpi"] = 120

CPU_HZ = 600_000_000

# Representative zero-voltage captures, one per stage.
timing_runs = [
    ("O0 first", "first", 1, "#d62728"),
    ("priority", "priority", 2, "#ff7f0e"),
    ("priority-O2", "o2", 2, "#1f77b4"),
    ("coherent-O2", "coherent", 2, "#2ca02c"),
]
timing = []
for label, dataset, capture_index, color in timing_runs:
    with gzip.open(BASE / "data/raw" / dataset / "raw_console.json.gz", "rt", encoding="utf-8") as f:
        raw = json.load(f)
    capture = raw["captures"][capture_index]
    rows = capture["rows"]
    cyc = np.array([row["cyc"] for row in rows], dtype=np.int64)
    intervals = ((cyc[1:] - cyc[:-1]) & 0xFFFFFFFF) * 1e6 / CPU_HZ
    lag = np.array([row["seq3b"] - row["seq2"] for row in rows], dtype=np.int64)
    timing.append({
        "label": label, "dataset": dataset, "capture": capture_index,
        "condition": capture["condition"], "repeat": capture.get("repeat"),
        "intervals_us": intervals, "lag": lag, "color": color,
    })

fig, axes = plt.subplots(2, 1, figsize=(14, 10), sharex=True)
for item in timing:
    axes[0].plot(np.arange(1, len(item["intervals_us"]) + 1),
                 item["intervals_us"], linestyle="none", marker=".",
                 markersize=2.5, alpha=0.75, color=item["color"],
                 label=item["label"])
    axes[1].plot(np.arange(len(item["lag"])), item["lag"], linestyle="none",
                 marker=".", markersize=2.5, alpha=0.75,
                 color=item["color"], label=item["label"])
axes[0].axhline(50.0, color="0.55", linewidth=0.8)
axes[0].set_ylabel("start_cycle 间隔（µs）")
axes[0].set_title("代表性零电压 PWM 帧：控制采集点 start_cycle 间隔（原始点，不平滑）")
axes[0].legend(loc="upper right", fontsize=9)
axes[0].grid(True, alpha=0.25)
axes[1].axhline(0.0, color="0.55", linewidth=0.8)
axes[1].set_ylabel("ADC3 计数差（seq3b - seq2）")
axes[1].set_xlabel("样本序号（1024 点；名义 20 kHz）")
axes[1].set_title("同一采集的 ADC3 完成计数差（原始点）")
axes[1].legend(loc="lower left", fontsize=9)
axes[1].grid(True, alpha=0.25)
fig.text(
    0.5, 0.01,
    "图中为各阶段一次代表性 capture；原始位/时间戳保留在 gzip JSON，未平滑。"
    "不同阶段条件相同（零电压 PWM），但不是同一物理时间。",
    ha="center", fontsize=9,
)
fig.tight_layout(rect=[0, 0.035, 1, 0.98])
fig.savefig(FIG / "dma_timing_compare.png", dpi=160, bbox_inches="tight")
plt.close(fig)

# Low-gain 10 RPM target/feedback/position comparison.
speed_runs = [
    ("priority-O0", "dma_speed_gain.json", "#ff7f0e"),
    ("priority-O2", "dma_speed_o2_gain.json", "#1f77b4"),
    ("coherent-O2", "dma_speed_coherent_gain.json", "#2ca02c"),
]
speed_stats = {}
fig, axes = plt.subplots(3, 1, figsize=(14, 12), sharex=False)
for label, filename, color in speed_runs:
    data = json.loads((SRC / filename).read_text(encoding="utf-8"))
    target_pps = np.asarray(data["scope"]["1"], dtype=float)
    position = np.asarray(data["scope"]["2"], dtype=float)
    dt = float(data["dt_s"])
    mask = target_pps != 0.0
    idx = np.flatnonzero(mask)
    if len(idx) < 2:
        raise SystemExit(f"{filename}: no nonzero target")
    target_rpm = target_pps * 60.0 / 16384.0
    feedback_rpm = np.diff(position) * 60.0 / (16384.0 * dt)
    start = int(idx[0])
    stop = int(idx[-1])
    x_target = (np.arange(len(target_pps)) - start) * dt
    x_fb = (np.arange(1, len(position)) - start) * dt
    pos_rel = position - position[start]
    axes[0].plot(x_target, target_rpm, linewidth=1.1, color=color, label=label)
    axes[1].plot(x_fb, feedback_rpm, linewidth=0.8, color=color, alpha=0.85, label=label)
    axes[2].plot(x_target, pos_rel, linewidth=1.0, color=color, label=label)
    speed_stats[label] = {
        "dt_s_nominal": dt,
        "target_mask_start": start,
        "target_mask_end": stop,
        "target_mask_s_nominal": round((stop - start + 1) * dt, 4),
        "target_rpm_mean": round(float(target_rpm[mask].mean()), 4),
        "target_rpm_std": round(float(target_rpm[mask].std()), 4),
        "target_rpm_peak": round(float(target_rpm[mask].max()), 4),
        "feedback_rpm_mean": round(float(feedback_rpm[mask[1:]].mean()), 4),
        "feedback_rpm_std": round(float(feedback_rpm[mask[1:]].std()), 4),
        "feedback_rpm_peak": round(float(feedback_rpm[mask[1:]].max()), 4),
        "position_net_counts": int(position[stop] - position[start]),
        "position_diff_mean_rpm": round(
            float((position[stop] - position[start]) * 60.0 /
                  (16384.0 * (stop - start) * dt)), 4
        ),
    }

axes[0].set_ylabel("目标速度（RPM）")
axes[0].set_title("低增益 10 RPM 对照：scope channel1 实际目标（非 QTimer 事件）")
axes[0].set_ylim(0, 12)
axes[1].set_ylabel("反馈速度（RPM）")
axes[1].set_title("由 position_counts 差分得到；约 8 ms 名义采样，非严格起止")
axes[1].set_ylim(-60, 400)
axes[2].set_ylabel("位置变化（counts）")
axes[2].set_title("目标期间位置净变化（相对目标起点）")
axes[2].set_xlabel("相对目标 mask 起点的时间（s，名义 8 ms/点）")
for ax in axes:
    ax.legend(loc="upper right", fontsize=9)
    ax.grid(True, alpha=0.25)
fig.text(
    0.5, 0.01,
    "target 使用 channel1 p/s×60/16384；反馈用位置差分；scope 名义 dt=8 ms，"
    "实际起止/抖动未由 QTimer 事件严格对齐。",
    ha="center", fontsize=9,
)
fig.tight_layout(rect=[0, 0.035, 1, 0.98])
fig.savefig(FIG / "dma_speed_lowgain_compare.png", dpi=160, bbox_inches="tight")
plt.close(fig)

# Raw sigma range from analyses.
sigma_values = []
for ds in ["first", "confirm", "priority", "o2", "coherent"]:
    analysis = json.loads((BASE / "data/analysis" / ds / "analysis.json").read_text(encoding="utf-8"))
    for capture in analysis["captures"]:
        for phase in ["u", "v", "w"]:
            sigma_values.append(float(capture["channels"][phase]["std_equiv_mA"]))

current = json.loads((BASE / "data/current/dma_current_regression.json").read_text(encoding="utf-8"))
summary = {
    "raw_sigma_mA": {
        "min": round(min(sigma_values), 4),
        "max": round(max(sigma_values), 4),
        "n_phase_values": len(sigma_values),
    },
    "speed": speed_stats,
    "current_regression": current.get("steady"),
    "timing_representative": [
        {"label": item["label"], "dataset": item["dataset"],
         "capture": item["capture"], "condition": item["condition"],
         "repeat": item["repeat"]}
        for item in timing
    ],
}
(BASE / "data" / "summary.json").write_text(
    json.dumps(summary, ensure_ascii=False, indent=2), encoding="utf-8"
)
print(json.dumps(summary, ensure_ascii=False, indent=2))
print("figures", FIG / "dma_timing_compare.png", FIG / "dma_speed_lowgain_compare.png")
