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

fig, ax = plt.subplots()

col = list(df.columns)
x_ticks = list(df[col[0]])

df.plot(x = col[0], y = [col[1], col[2]])
# df.plot(x = col[0], y = col[1])
plt.grid(True)

# plt.title('Area of Circle when $r=10m$', fontweight = 'bold')
plt.title('Area of Circle when $r=7m$', fontweight = 'bold')

plt.xlabel('Point Count', fontweight='bold')
plt.xscale('log')
# plt.gca().yaxis.set_major_formatter(mtick.FormatStrFormatter('%.0f'))
plt.xticks(x_ticks)

# plt.yticks(np.arange(530, 544))
# plt.yticks(np.arange(314, 324))
plt.ylabel('Area Value $(m^2)$', fontweight='bold')
# plt.yscale('log')
# plt.gca().yaxis.set_major_formatter(mtick.FormatStrFormatter('%.0f'))

plt.minorticks_off()
# plt.show()
plt.savefig(outname, bbox_inches='tight')