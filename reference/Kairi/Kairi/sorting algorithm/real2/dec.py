import random

x = []
for i in range(100000):
    res = random.randint(-50000, 50000)
    res = res / 7
    x.append(round(res,6))

for i in range(100000):
    print(x[i])


