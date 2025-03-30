import pandas as pd
import matplotlib.pyplot as plt

file_path = "rank_map.csv"
df = pd.read_csv(file_path)

plt.figure(figsize=(12, 6))

for column in df.columns:
    if column != "Rank":
        filtered_df = df[df[column] > 0]

        plt.scatter(filtered_df["Rank"], filtered_df[column], marker='o', label=column, alpha=0.7)

plt.xlabel("Ranga slowa")
plt.ylabel("Czestotliwosc wystepowania")

plt.xscale("log")
plt.yscale("log")

plt.title("Wykres prawa Zipfa dla roznych tekstow")

plt.xticks(rotation=45)

plt.grid(axis='y', linestyle="--", alpha=0.6)

plt.legend(["Pan tadeusz", "Romeo i Julia"])

file_name = "wykres.png"
plt.savefig(file_name, dpi=300)

plt.close()
