import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

file_path = "rank_map.csv"
df = pd.read_csv(file_path)

plt.figure(figsize=(12, 6))

legend_labels = []

for column in df.columns:
    if column != "Rank":
        filtered_df = df[df[column] > 0]

        log_rank = np.log10(filtered_df["Rank"])
        log_freq = np.log10(filtered_df[column])

        slope, intercept = np.polyfit(log_rank, log_freq, 1)

        plt.scatter(filtered_df["Rank"], filtered_df[column], marker = 'o', alpha = 0.7)

        rank_range = np.linspace(filtered_df["Rank"].min(), filtered_df["Rank"].max(), 100)
        freq_fit = 10**(intercept + slope * np.log10(rank_range))

        line, = plt.plot(rank_range, freq_fit, linewidth = 2, label = f"{column} (β = {slope:.2f})")

        legend_labels.append(line)

plt.xlabel("Ranga słowa")
plt.ylabel("Częstotliwość występowania")

plt.xscale("log")
plt.yscale("log")

plt.title("Wykres prawa Zipfa dla różnych tekstów")

plt.xticks(rotation=45)

plt.grid(axis='y', linestyle="--", alpha = 0.6)

plt.legend(handles = legend_labels)

file_name = "wykres.png"
plt.savefig(file_name, dpi = 300)

plt.close()
