import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

def zadanie_1():
    df = pd.read_csv("data/radius_eden.csv")

    steps = df['step']
    radius = df['radius']

    N = steps
    y_theoretical = np.sqrt(N)

    plt.figure(figsize=(8,6))

    plt.scatter(steps, radius, color='blue', label='Promień klastra')

    plt.plot(steps, y_theoretical, color='red', linestyle='--', label=r'$y = N^{1/2}$')

    plt.xscale('log')
    plt.yscale('log')

    plt.xlabel('Krok symulacji (log scale)')
    plt.ylabel('Promień klastra (log scale)')
    plt.title('Promień klastra w czasie (log-log scale)')
    plt.legend()
    plt.grid(True, which="both", ls="--", lw=0.5)

    plt.savefig('wykres_eden.png')
    plt.show()


def zadanie_2():

    df = pd.read_csv("data/radius_DLA.csv")

    particles = df['particles']
    radius = df['radius']

    theory = np.power(particles, 0.58)

    plt.figure(figsize=(8,6))
    plt.scatter(particles, radius, label='DLA (symulacja)', color='blue')
    plt.plot(particles, theory, label=r'$N^{0.58}$', linestyle='--', color='red')

    plt.xscale('log')
    plt.yscale('log')
    plt.xlabel('Liczba cząsteczek (log)')
    plt.ylabel('Promień klastra (log)')
    plt.title('Skalowanie promienia klastra DLA')
    plt.grid(True, which='both', ls='--')
    plt.legend()
    plt.tight_layout()
    plt.savefig('wykres_DLA.png')
    plt.show()


#zadanie_1()
zadanie_2()