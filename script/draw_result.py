import os, sys
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

units = ["Byte", "kB", "MB", "GB", "TB", "PB"]
plt_dpi = 200


def get_size_divisor(size_byte):
    divisor, unit_index = 1, 0
    while size_byte > 1024:
        size_byte /= 1024
        divisor, unit_index = divisor * 1024, unit_index + 1
    return divisor, units[unit_index]


def draw_traffic_timing(traffic_timing_path):
    data = pd.read_csv(traffic_timing_path)
    grouped = data.groupby("network_id")
    for name, group in grouped:
        plt.figure(
            figsize=(12, 4),
            dpi=plt_dpi,
        )
        data_x = group["time_ns"] / 1000000000
        data_y = group["size_byte"]
        divisor, unit = get_size_divisor(data_y[data_y != 0].min())
        plt.plot(data_x, data_y / divisor, linewidth=1)
        plt.xlabel(f"Time (s)")
        plt.ylabel(f"Size ({unit})")
        plt.title(f"Traffic on Network {name} ({unit})")
        plt.savefig(
            f"{os.path.dirname(traffic_timing_path)}/traffic_timing_network_{name}.png"
        )
        plt.close()


def draw_traffic_heatmap(traffic_heatmap_path):
    plt.figure(figsize=(12, 10), dpi=plt_dpi)
    data = pd.read_csv(traffic_heatmap_path, header=None)
    x_labels = data.iloc[0, 1:].tolist()
    y_labels = data.iloc[1:, 0].tolist()
    data = data.iloc[1:, 1:]
    data = data.astype(float)
    max_value = data.max().max()
    min_value = data[data != 0].min().min()
    divisor, unit = get_size_divisor(min_value)
    plt.title(f"Traffic Heatmap ({unit})")
    data, max_value, min_value = (
        data / divisor,
        max_value / divisor,
        min_value / divisor,
    )
    sns.heatmap(
        data,
        annot=True,
        fmt="g",
        cmap="viridis",
        xticklabels=x_labels,
        yticklabels=y_labels,
        vmin=min_value,
        vmax=max_value,
    )
    plt.savefig(os.path.dirname(traffic_heatmap_path) + "/traffic_heatmap.png")
    plt.close()


if __name__ == "__main__":
    result_path = sys.argv[1] if len(sys.argv) > 1 else "result"
    draw_traffic_timing(result_path + "/traffic_timing.csv")
    draw_traffic_heatmap(result_path + "/traffic_heatmap.csv")
    print("drawing results completed")
