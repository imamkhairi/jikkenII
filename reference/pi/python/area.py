import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
times = 5
kaisuu = 10

res_dr = "kekka/area1.csv"
df = pd.read_csv(res_dr, sep=" ")

x = [1000, 10000, 100000, 1000000, 10000000]

rironchi = [49*np.pi for x in range(len(x))]
#rironchi = [(lambda x: np.format_float_scientific(np.pi, precision=3))(x) for x in range(len(x))] 

jikken_pi = np.zeros(len(x),dtype=float)
gosa = np.zeros(len(x), dtype=float)

start = 0
end   = times
for i in range(len(x)):
    jikken_pi[i] = df["area"][start:end].sum()/times
    gosa[i] = df["gosa"][start:end].sum()/times
    start += times
    end += times


#jikken_pi = [(lambda x: np.format_float_scientific(x, precision=3))(x) for x in jikken_pi] 
#gosa = [(lambda x: np.format_float_scientific(x, precision=3))(x) for x in gosa]

a = np.arange(len(x))

fig = plt.figure(1, figsize=(9,5))
#ax1 = plt.subplot(111)
ax2 = plt.subplot(111)

#ax1.invert_yaxis()
#ax1.plot(a, jikken_pi, color='blue')
#ax1.plot(a, rironchi, color="red")
#ax1.xaxis.set_ticks(a)
#ax1.xaxis.set_ticklabels(x)
#ax1.grid()
#ax1.legend(["Test Result", "Theory Result"],fancybox=True, loc="lower right")
ax2.set_xlabel("N value", fontsize=16)
ax2.invert_yaxis()
ax2.plot(a, gosa, color='blue')
ax2.xaxis.set_ticks(a)
ax2.xaxis.set_ticklabels(x)
ax2.grid()
ax2.legend(["Error Value"],fancybox=True, loc="lower right")


#ax1.xaxis.set_major_locator(plt.MaxNLocator(9))
ax2.xaxis.set_major_locator(plt.MaxNLocator(9))

#fig.text(0.5, 0.04, 'N value', ha='center', va='center',size=16)
fig.text(0.03, 0.5, 'PI value', ha='center', va='center', rotation='vertical', size=16)

fig.savefig("grph/area23.png")
