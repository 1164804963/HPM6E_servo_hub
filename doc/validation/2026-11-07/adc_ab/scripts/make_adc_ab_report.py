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

BASE = Path(__file__).resolve().parent.parent
DATA = BASE / "data" / "measurements"
FIG = BASE / "figures"
FIG.mkdir(parents=True, exist_ok=True)

GROUPS = ["original", "baseline", "window80", "clock8", "restored"]
GROUP_LABEL = {
    "original": "原固件",
    "baseline": "baseline 20/4",
    "window80": "window80 80/4",
    "clock8": "clock8 20/8",
    "restored": "恢复原固件",
}
SOURCE_GROUPS = ["baseline", "window80", "clock8"]
CONDITIONS = ["pwm_off", "zero_voltage_pwm_on"]
COND_LABEL = {
    "pwm_off": "PWM 关闭",
    "zero_voltage_pwm_on": "零电压 PWM",
}
PHASES = ["U", "V", "W"]
K_MA_PER_COUNT = 0.503540039

font_path = Path(r"C:/Windows/Fonts/msyh.ttc")
if font_path.exists():
    font_manager.fontManager.addfont(str(font_path))
plt.rcParams["font.family"] = "Microsoft YaHei"
plt.rcParams["axes.unicode_minus"] = False
plt.rcParams["figure.dpi"] = 120

result = {}
max_summary_delta = 0.0
for group in GROUPS:
    raw = json.loads((DATA / group / "raw_console.json").read_text(encoding="utf-8"))
    summary = json.loads((DATA / group / "summary.json").read_text(encoding="utf-8"))
    result[group] = {"label": GROUP_LABEL[group], "conditions": {}}
    for cond in CONDITIONS:
        rows = raw["conditions"][cond]
        if len(rows) != 100:
            raise SystemExit(f"{group}/{cond}: expected 100 rows, got {len(rows)}")
        counts = np.array([r["adc"][:3] for r in rows], dtype=float)
        if counts.shape != (100, 3) or not np.isfinite(counts).all():
            raise SystemExit(f"{group}/{cond}: bad ADC matrix")
        summary_std = np.array(
            [summary["conditions"][cond][phase]["std_counts"] for phase in PHASES],
            dtype=float,
        )
        std0 = counts.std(axis=0, ddof=0)
        std1 = counts.std(axis=0, ddof=1)
        ddof = 0 if np.max(np.abs(std0 - summary_std)) <= np.max(np.abs(std1 - summary_std)) else 1
        std_counts = counts.std(axis=0, ddof=ddof)
        max_summary_delta = max(
            max_summary_delta,
            float(np.max(np.abs(std_counts - summary_std))),
        )
        result[group]["conditions"][cond] = {
            "n": int(counts.shape[0]),
            "mean_counts": [round(float(x), 3) for x in counts.mean(axis=0)],
            "std_counts": [round(float(x), 3) for x in std_counts],
            "sigma_mA": [round(float(x * K_MA_PER_COUNT), 3) for x in std_counts],
            "pp_counts": [int(x) for x in (counts.max(axis=0) - counts.min(axis=0))],
            "summary_std_counts": [round(float(x), 3) for x in summary_std],
            "std_ddof": ddof,
            "time_span_s": round(float(rows[-1]["time"] - rows[0]["time"]), 4),
            "final_disabled": bool(summary.get("final_disabled", False)),
        }

if max_summary_delta > 0.01:
    raise SystemExit(f"summary/raw std mismatch: {max_summary_delta:.6f} counts")

# Figure 1: U phase, demeaned, the three source variants, shared Y axis.
fig, axes = plt.subplots(1, 2, figsize=(14, 5.8), sharey=True)
colors = {"baseline": "#1f77b4", "window80": "#ff7f0e", "clock8": "#2ca02c"}
markers = {"baseline": "o", "window80": "s", "clock8": "^"}
all_demeaned = []
for group in SOURCE_GROUPS:
    for cond in CONDITIONS:
        counts = np.array(
            [r["adc"][0] for r in json.loads(
                (DATA / group / "raw_console.json").read_text(encoding="utf-8")
            )["conditions"][cond]],
            dtype=float,
        )
        all_demeaned.append((counts - counts.mean()) * K_MA_PER_COUNT)
y_limit = max(1.0, float(np.max(np.abs(np.concatenate(all_demeaned)))) * 1.08)
for ax, cond in zip(axes, CONDITIONS):
    for group in SOURCE_GROUPS:
        rows = json.loads(
            (DATA / group / "raw_console.json").read_text(encoding="utf-8")
        )["conditions"][cond]
        counts = np.array([r["adc"][0] for r in rows], dtype=float)
        y = (counts - counts.mean()) * K_MA_PER_COUNT
        ax.plot(
            np.arange(1, len(y) + 1),
            y,
            linestyle="none",
            marker=markers[group],
            markersize=3.2,
            color=colors[group],
            alpha=0.8,
            label=GROUP_LABEL[group],
        )
    ax.axhline(0.0, color="0.55", linewidth=0.8)
    ax.set_title(COND_LABEL[cond])
    ax.set_xlabel("样本序号（每条件 100 点；约 35 ms/点，非 20 kHz）")
    ax.grid(True, alpha=0.25)
    ax.set_xlim(0.5, 100.5)
    ax.set_ylim(-y_limit, y_limit)
axes[0].set_ylabel("U 相等效 ADC 去均值（mA；1 count=0.503540039 mA）")
axes[0].legend(loc="upper right", fontsize=9, framealpha=0.9)
fig.suptitle("三个源码版本 U 相原始 ADC 去均值时序（未插值）")
fig.text(
    0.5,
    0.01,
    "仅串口 100 点/条件；采样间隔约 35 ms，不是 20 kHz 波形；纵轴统一，单位为 ADC 等效电流而非外部实测电流。",
    ha="center",
    fontsize=9,
)
fig.tight_layout(rect=[0, 0.04, 1, 0.94])
fig.savefig(FIG / "adc_u_demeaned.png", dpi=160, bbox_inches="tight")
plt.close(fig)

# Figure 2: three-phase std, all five groups and both conditions.
fig, axes = plt.subplots(1, 2, figsize=(14, 5.8), sharey=True)
x = np.arange(len(GROUPS))
width = 0.26
phase_colors = {"U": "#1f77b4", "V": "#ff7f0e", "W": "#2ca02c"}
for ax, cond in zip(axes, CONDITIONS):
    for idx, phase in enumerate(PHASES):
        vals = [result[g]["conditions"][cond]["sigma_mA"][idx] for g in GROUPS]
        ax.bar(
            x + (idx - 1) * width,
            vals,
            width,
            color=phase_colors[phase],
            label=f"{phase} 相",
        )
    ax.set_xticks(x)
    ax.set_xticklabels([GROUP_LABEL[g] for g in GROUPS], rotation=15, ha="right")
    ax.set_title(COND_LABEL[cond])
    ax.set_ylabel("ADC 等效 σ（mA）")
    ax.grid(True, axis="y", alpha=0.25)
    ax.legend(fontsize=9)
axes[0].set_ylim(0, max(
    result[g]["conditions"][c]["sigma_mA"][i]
    for g in GROUPS for c in CONDITIONS for i in range(3)
) * 1.18)
fig.suptitle("三相 ADC 等效标准差比较（100 点/条件）")
fig.text(
    0.5,
    0.01,
    "σ 由原始 st 三相计数计算；三相不是同拍采样，不能据此计算三相和/相关性。",
    ha="center",
    fontsize=9,
)
fig.tight_layout(rect=[0, 0.04, 1, 0.94])
fig.savefig(FIG / "adc_three_phase_std.png", dpi=160, bbox_inches="tight")
plt.close(fig)

(BASE / "data" / "sigma_table.json").write_text(
    json.dumps(result, ensure_ascii=False, indent=2), encoding="utf-8"
)
print("max_summary_std_delta_counts", round(max_summary_delta, 6))
for cond in CONDITIONS:
    print(COND_LABEL[cond])
    for group in GROUPS:
        r = result[group]["conditions"][cond]
        print(group, "n=", r["n"], "sigma_mA=", r["sigma_mA"], "ddof=", r["std_ddof"])
print("figures", FIG / "adc_u_demeaned.png", FIG / "adc_three_phase_std.png")
