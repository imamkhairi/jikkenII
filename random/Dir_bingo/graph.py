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

# df.plot(x = col[0], y = [col[1], col[2]])
df.plot(x = col[0], y = col[3])
plt.grid(True)

plt.xlabel('Count', fontweight='bold')
# plt.xscale('log')
plt.xticks(x_ticks)

plt.ylabel('Success Probability', fontweight='bold')
# plt.yscale('log')
plt.gca().yaxis.set_major_formatter(mtick.FormatStrFormatter('%.0e'))

plt.minorticks_off()
# plt.show()
plt.savefig(outname, bbox_inches='tight')