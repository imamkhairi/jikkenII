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
# y_ticks = np.arange(0,140)

# df.plot(x = col[0], y = [col[1], col[2]], marker = '.')
y1 = [x*1.1 for x in df.iloc[:,1]]
y2 = [x*0.9 for x in df.iloc[:,1]]
y3 = [x*1.2 for x in df.iloc[:,1]]
y4 = [x*0.8 for x in df.iloc[:,1]]

# print(y1)
# print(df.iloc[:,1])
x = df.iloc[:,0]
# df.plot(x = col[0], y = [col[1], col[2]])

plt.plot(x, df.iloc[:,3], label = "Error_1")
plt.plot(x, df.iloc[:,6], label = "Error_2")
plt.plot(x, df.iloc[:,9], label = "Error_3")


# plt.plot(x, df.iloc[:,1], label = "Actual")
# plt.plot(df.iloc[:,0], y1, label = "110%% of Actual")
# plt.plot(df.iloc[:,0], y2, label = "90%% of Actual")
# plt.fill_between(x, y1, y2,color='C0', alpha = 0.2)
# plt.fill_between(x, y1, y3,color='C1', alpha = 0.2)
# plt.fill_between(x, y2, y4,color='C1', alpha = 0.2)
plt.grid(True)

# plt.title('Getting Same Dice Error', fontweight = 'bold')
# plt.title('Getting Same Dice Error', fontweight = 'bold')

plt.xlabel('Iteration Count', fontweight='bold')
plt.xscale('log')
# plt.xticks(x_ticks[::5])
# plt.yticks(y_ticks[::10])


# print(x_ticks)

# plt.ylabel('Error', fontweight='bold')
plt.ylabel('Absolute Error [%]', fontweight='bold')
# plt.yscale('log')
# plt.ylim(-8e-09, 2e-08)
# def y_fmt(x, y):
#     return '{:3.1e}'.format(x).replace('e', 'e')

# plt.gca().xaxis.set_major_formatter(mtick.FuncFormatter(y_fmt))
# plt.gca().yaxis.set_major_formatter(mtick.FuncFormatter(y_fmt))

plt.legend(loc="upper right")
plt.minorticks_off()
# plt.show()
plt.savefig(outname, bbox_inches='tight')