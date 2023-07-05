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

# df.plot(x = col[0], y = [col[1], col[2]], marker = '.')
df.plot(x = col[0], y = [col[1], col[2]])
# df.plot(x = col[0], y = col[2])
plt.grid(True)

# plt.title('Getting Same Dice Probability', fontweight = 'bold')
plt.title('Getting Same Dice Probability', fontweight = 'bold')

plt.xlabel('Simulation Count', fontweight='bold')
# plt.xscale('log')
plt.xticks(x_ticks[::20])

# print(x_ticks)

# plt.ylabel('Probability', fontweight='bold')
plt.ylabel('Probability[%]', fontweight='bold')
# plt.yscale('log')
# plt.ylim(-8e-09, 2e-08)
def y_fmt(x, y):
    return '{:3.1e}'.format(x).replace('e', 'e')

plt.gca().xaxis.set_major_formatter(mtick.FuncFormatter(y_fmt))
plt.gca().yaxis.set_major_formatter(mtick.FuncFormatter(y_fmt))

plt.minorticks_off()
# plt.show()
plt.savefig(outname, bbox_inches='tight')