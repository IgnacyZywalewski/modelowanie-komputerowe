import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('../bin/data/distances.csv')

plt.plot(df['step'], df['system_1'], label='Układ 1')
plt.plot(df['step'], df['system_2'], label='Układ 2')
plt.plot(df['step'], df['system_3'], label='Układ 3')

plt.xlabel('Krok')
plt.ylabel('Średnia odległość ciał')
plt.title('Wykres średnich odległości dla 3 różnych układów początkowych')
plt.legend(loc = 'upper left')
plt.grid()
plt.savefig("../bin/data/wykres.png")
plt.close()