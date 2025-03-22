import pandas as pd
import matplotlib.pyplot as plt
import os

file_path = "all_simulations.csv"
df = pd.read_csv(file_path)

os.makedirs("wyniki", exist_ok=True)

for column in df.columns[1:]:
    plt.figure(figsize=(12, 6))
    plt.plot(df["Iteration"], df[column], color='b', alpha=0.7)
    
    plt.xlabel("Iteracja")
    plt.ylabel("Procent zywych komorek (%)")
    plt.title(f"Wykres zmiany zywych komorek w czasie dla ({column})")
    plt.xticks(rotation=45)
    plt.grid(axis='y', linestyle="--", alpha=0.6)

    file_name = f"wyniki/{column}.png"
    plt.savefig(file_name, dpi=300)

    plt.close()
