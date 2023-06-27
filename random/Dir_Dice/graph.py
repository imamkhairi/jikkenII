import pandas as pd
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

# df.plot(x = col[0], y = [col[4], col[5]])
df.plot(x = col[0], y = [col[1], col[2]])
# df.plot(x = col[0], y = [col[2], col[3]])
# df.plot(x = col[0], y = col[5])
plt.grid(True)

plt.xlabel('Count', fontweight='bold')
plt.xscale('log')
plt.xticks(x_ticks)

# plt.ylabel('Probability', fontweight='bold')
plt.ylabel('Probability', fontweight='bold')
# plt.yscale('log')
# plt.ylim(-8e-09, 2e-08)
def y_fmt(x, y):
    return '{:2.1e}'.format(x).replace('e', 'e')

plt.gca().yaxis.set_major_formatter(mtick.FuncFormatter(y_fmt))

plt.minorticks_off()
# plt.show()
plt.savefig(outname, bbox_inches='tight')