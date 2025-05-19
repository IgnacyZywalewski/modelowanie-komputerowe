import matplotlib.pyplot as plt
import pandas as pd
import os
from mpl_toolkits.mplot3d import Axes3D

os.makedirs("wykresy", exist_ok=True)

def zadanie_1():
    filename = "dane/zadanie_1.csv"
    df = pd.read_csv(filename)

    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 6), sharey=True)

    ax1.bar(df["value"], df["count_1"], color='blue', width=1.0)
    ax1.set_title("Mersenne Twister")
    ax1.set_xlabel("Wartość")
    ax1.set_ylabel("Częstość występowania")

    ax2.bar(df["value"], df["count_2"], color='red', width=1.0)
    ax2.set_title("Generator Modulo")
    ax2.set_xlabel("Wartość")

    plt.tight_layout()
    plt.savefig("wykresy/histogram_1.png")
    plt.show()

def zadanie_2_2D():
    df = pd.read_csv("dane/zadanie_2_2D.csv")

    plt.figure(figsize=(10, 10))
    plt.title("Ścieżki 10 spacerów losowych (2D)")
    plt.xlabel("x")
    plt.ylabel("y")
    plt.grid(True)
    plt.axis("equal")

    for i in range(10):
        x_col = f"walk_{i+1}_x"
        y_col = f"walk_{i+1}_y"
        plt.plot(df[x_col], df[y_col], label=f"Spacer {i+1}")

    plt.legend()
    plt.tight_layout()
    plt.savefig("wykresy/spacery_2d.png")
    plt.show()

def zadanie_2_3D():
    df = pd.read_csv("dane/zadanie_2_3D.csv")

    fig = plt.figure(figsize=(12, 8))
    ax = fig.add_subplot(111, projection='3d')
    ax.set_title("Ścieżki 10 spacerów losowych (3D)")
    ax.set_xlabel("x")
    ax.set_ylabel("y")
    ax.set_zlabel("z")

    for i in range(10):
        x_col = f"walk_{i+1}_x"
        y_col = f"walk_{i+1}_y"
        z_col = f"walk_{i+1}_z"
    
        ax.plot(df[x_col], df[y_col], df[z_col], label=f"Spacer {i+1}")

    ax.legend()
    plt.tight_layout()
    plt.savefig("wykresy/spacery_3d.png")
    plt.show()

def zadanie_3():
    filename = "dane/zadanie_3.csv"

    df = pd.read_csv(filename)

    plt.figure(figsize=(10, 6))
    plt.bar(df["position"], df["value"], color="blue", width=0.8)

    plt.title("Końcowe pozycje 10000 spacerów losowych (1D)")
    plt.xlabel("Końcowa pozycja")
    plt.ylabel("Liczba spacerów")
    plt.grid(True)

    plt.tight_layout()
    plt.savefig("wykresy/histogram_3.png")
    plt.show()


zadanie_1()
zadanie_2_2D()
zadanie_2_3D()
zadanie_3()