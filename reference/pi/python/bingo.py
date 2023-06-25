import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
times = 10
kaisuu = 4

res_dr = "kekka/bingo.csv"
df = pd.read_csv(res_dr, sep=" ")

x = [10000]
for nilai in range(0,kaisuu-1):
    kekka = x[nilai] *10
    x.append(kekka)

rironchi4 = [0.0000032910, 0.0000032910, 0.0000032910, 0.0000032910]
rironchi7 = [0.0000727720, 0.0000727720, 0.0000727720, 0.0000727720]
rironchi71 = [0.0000013905, 0.0000013905, 0.0000013905, 0.0000013905]
miN = np.zeros(len(x),dtype=float)
miD = np.zeros(len(x),dtype=float)
maX = np.zeros(len(x),dtype=float)

start = 0
end   = times
for i in range(len(x)):
    miN[i] = df["min"][start:end].sum()/times
    miD[i] = df["mid"][start:end].sum()/times
    maX[i] = df["max"][start:end].sum()/times
    start += times
    end += times

for i in range(len(x)):
    miN[i] = miN[i] / x[i]
    miD[i] = miD[i] / x[i]
    maX[i] = maX[i] / x[i]
    
#jikken_pi = [(lambda x: np.format_float_scientific(x, precision=3))(x) for x in jikken_pi] 
#gosa = [(lambda x: np.format_float_scientific(x, precision=3))(x) for x in gosa]

a = np.arange(len(x))

fig = plt.figure(1, figsize=(10,7))
ax1 = plt.subplot(111)


ax1.invert_yaxis()
ax1.plot(a, maX, color='blue')
ax1.plot(a, rironchi71, color="red")

ax1.xaxis.set_ticks(a)
ax1.xaxis.set_ticklabels(x)
ax1.grid()
#ax1.legend(["Test Result", "Theory Result"],fancybox=True, loc="upper right")

fig.text(0.5, 0.04, 'N value', ha='center', va='center',size=16)
fig.text(0.03, 0.5, 'Percentage', ha='center', va='center', rotation='vertical', size=16)

fig.savefig("grph/bingo71.png")
