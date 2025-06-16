import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def zadanie_1():
    df = pd.read_csv('data/zadanie_1/zadanie_1.csv')
    plt.figure(figsize=(10, 6))
    plt.plot(df['dist'], df['sum_dist'], linewidth=1)
    plt.title('Wykres zależności pomiędzy odległością początkową, a odległością sumy szeregów')
    plt.xlabel('Odległość początkowa')
    plt.ylabel('Odlegość pomiędzy sumą szeregów')
    plt.grid(True)
    plt.tight_layout()
    plt.savefig('data/zadanie_1/zadanie_1.png')
    plt.show()


def zadanie_2():
    df = pd.read_csv("data/zadanie_2/zadanie_2.csv")
    plt.figure(figsize=(12, 8))
    plt.scatter(df['r'], df['x'], s=0.5, color='black')
    plt.title("Wykres równania logistycznego dla r od 2.4 do 4.0")
    plt.xlabel("r")
    plt.ylabel("x")
    plt.grid(True, linestyle='--', alpha=0.3)
    plt.tight_layout()
    plt.savefig('data/zadanie_2/zadanie_2.png')
    plt.show()


def zadanie_3():
    df = pd.read_csv("data/zadanie_3/zadanie_3.csv")

    fig = plt.figure(figsize=(10, 7))
    ax = fig.add_subplot(111, projection='3d')
    ax.plot(df['x'], df['y'], df['z'], lw=0.5, color='blue')

    ax.set_title("Wykres motyla Lorenza")
    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    ax.set_zlabel("Z")
    plt.tight_layout()
    plt.savefig('data/zadanie_3/zadanie_3.png')
    plt.show()


def zadanie_4():
    p1 = pd.read_csv("data/zadanie_4/zadanie_4_1.csv")
    p2 = pd.read_csv("data/zadanie_4/zadanie_4_2.csv")

    plt.figure(figsize=(10, 4))
    plt.subplot(1, 2, 1)
    plt.plot(p1['a2'], p1['a2_v'], '.', markersize=1, color='blue')
    plt.title('Wykres fazowy – Wahadło 1')
    plt.xlabel('Kąt')
    plt.ylabel('Prędkość kątowa')
    plt.grid(True)

    plt.subplot(1, 2, 2)
    plt.plot(p2['a2'], p2['a2_v'], '.', markersize=1, color='red')
    plt.title('Wykres fazowy – Wahadło 2')
    plt.xlabel('Kąt')
    plt.ylabel('Prędkość kątowa')
    plt.grid(True)

    plt.tight_layout()
    plt.savefig('data/zadanie_4/zadanie_4.png')
    plt.show()


zadanie_1()
zadanie_2()
zadanie_3()
zadanie_4()
