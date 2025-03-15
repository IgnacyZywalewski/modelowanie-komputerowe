import pandas as pd
import matplotlib.pyplot as plt

file_path="gestosc.csv"
output_image="wykres.png"

df = pd.read_csv(file_path)

plt.figure(figsize=(12, 6))
plt.bar(df["Iteration"], df["AliveRatio"], color='b', alpha=0.7)

plt.xlabel("Iteracja")
plt.ylabel("Gestosc zywych komorek")
plt.title("Zmiana gestosci zywych komorek w czasie")
plt.xticks(rotation=45)
plt.grid(linestyle="--", alpha=0.6)

plt.savefig(output_image, dpi=300)
print(f"Wykres zapisany jako {output_image}")
