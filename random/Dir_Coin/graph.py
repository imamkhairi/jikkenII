import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.ticker as mtick
import sys

if len(sys.argv) != 3:
    print("Set File name and output filename")
    exit()
else: 
    filename = sys.argv[1]
    outname = sys.argv[2]

df = pd.read_csv(filename)

col = list(df.columns)
x_ticks = list(df[col[0]])

# df.plot(x = col[0], y = [col[1], col[2]])
df.plot(x = col[0], y = [col[1], col[2], col[3]])
# df.plot(x = col[0], y = col[1])
plt.grid(True)

plt.title('A Winning Game Probability', fontweight = 'bold')


plt.xlabel('Simulation Count', fontweight='bold')
plt.xscale('log')
plt.xticks(x_ticks)

plt.ylabel('A Win Probability', fontweight='bold')
plt.yticks(np.arange(0.1, 0.55, 0.05))
# plt.yscale('log')
# def y_fmt(x, y):
#     return '{:2.1e}'.format(x).replace('e', 'e')

# plt.gca().yaxis.set_major_formatter(mtick.FuncFormatter(y_fmt))
plt.gca().yaxis.set_major_formatter(mtick.FormatStrFormatter('%.3f'))

plt.minorticks_off()
# plt.show()
plt.savefig(outname, bbox_inches='tight')