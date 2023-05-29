import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
times = 10
kaisuu = 13

res_dr = "kekka/bingo1.csv"
df = pd.read_csv(res_dr, sep=" ")

x = [10000]
for nilai in range(0,kaisuu-1):
    kekka = x[nilai] + 40000
    x.append(kekka)
x.append(500000)

rironchi = [(lambda x: np.pi)(x) for x in range(len(x))]
#rironchi = [(lambda x: np.format_float_scientific(np.pi, precision=3))(x) for x in range(len(x))] 

jikken_pi = np.zeros(len(x),dtype=float)
gosa = np.zeros(len(x), dtype=float)

start = 0
end   = times
for i in range(len(x)):
    jikken_pi[i] = df["pi"][start:end].sum()/times
    gosa[i] = df["gosa"][start:end].sum()/times
    start += times
    end += times

gosa = [(lambda x: abs(np.pi - x))(x) for x in jikken_pi]
#jikken_pi = [(lambda x: np.format_float_scientific(x, precision=3))(x) for x in jikken_pi] 
#gosa = [(lambda x: np.format_float_scientific(x, precision=3))(x) for x in gosa]

a = np.arange(len(x))

fig = plt.figure(1, figsize=(10,7))
ax1 = plt.subplot(211)
ax2 = plt.subplot(212)

ax1.invert_yaxis()
ax1.plot(a, jikken_pi, color='blue')
ax1.plot(a, rironchi, color="red")
ax1.xaxis.set_ticks(a)
ax1.xaxis.set_ticklabels(x)
ax1.grid()
ax1.legend(["Test Result", "Theory Result"],fancybox=True, loc="upper right")

ax2.invert_yaxis()
ax2.plot(a, gosa, color='blue')
ax2.xaxis.set_ticks(a)
ax2.xaxis.set_ticklabels(x)
ax2.grid()
ax2.legend(["Error Value"],fancybox=True, loc="lower right")


ax1.xaxis.set_major_locator(plt.MaxNLocator(9))
ax2.xaxis.set_major_locator(plt.MaxNLocator(9))

fig.text(0.5, 0.04, 'N value', ha='center', va='center',size=16)
fig.text(0.03, 0.5, 'PI value', ha='center', va='center', rotation='vertical', size=16)

fig.savefig("grph/kekka2.png")
