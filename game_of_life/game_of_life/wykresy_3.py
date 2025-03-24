import pandas as pd
import matplotlib.pyplot as plt

file_path = "standard_error.csv"
df = pd.read_csv(file_path)

L_values = df["L"]
errors = df["Error"]

plt.figure(figsize=(10, 6))
plt.scatter(L_values, errors, label="Blad standardowy", color="blue")

plt.xlabel("Rozmiar ukladu L")
plt.ylabel("Blad standardowy")
plt.title("Wykres bledu standardowego sredniej w zaleznosci od rozmiaru ukladu L")
plt.grid(True, linestyle="--", alpha=0.7)

plt.savefig("wyniki/wykres_bledu.png", dpi=300)