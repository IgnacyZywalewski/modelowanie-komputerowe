import pandas as pd
import matplotlib.pyplot as plt

file_path = "rank_map.csv"
df = pd.read_csv(file_path)

plt.figure(figsize=(12, 6))
plt.plot(df["Rank"], df["Frequency"], marker='o', color='b', alpha=0.7)
    
plt.xlabel("Ranga slowa")
plt.ylabel("Czestotliwosc wystepowania")

plt.xscale("log")
plt.yscale("log")

plt.title("Wykres prawa Zipfa")
plt.xticks(rotation=45)
plt.grid(axis='y', linestyle="--", alpha=0.6)

file_name = "wykres.png"
plt.savefig(file_name, dpi=300)

plt.close()
