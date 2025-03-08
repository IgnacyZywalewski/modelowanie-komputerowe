import pandas as pd
import matplotlib.pyplot as plt
import os

os.makedirs("wykresy", exist_ok = True)

df = pd.read_csv("prawdopodobienstwo.csv")

titles = ["n = 100, bez więzienia", "n = 100 z więzieniem", "n = 1000000, bez więzienia", "n = 1000000, z więzieniem"]
cases = ["1", "2", "3", "4"]

i = 0

for case in cases:
    plt.figure(figsize=(12, 6))
    plt.bar(df["Field"], df[case], color="blue")
    plt.xlabel("Pole planszy")
    plt.ylabel("Prawdopodobieństwo (%)")
    plt.title(f"Prawdopodobieństwo trafienia na pola - ({titles[i]})")
    plt.savefig(f"wykresy/wykres_{i + 1}.png")
    plt.close()
    i = i + 1

print("Wykresy zostały zapisane w folderze 'wykresy/")
