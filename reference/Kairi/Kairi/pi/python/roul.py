import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
times = 10
kaisuu = 14

res_dr = "kekka/roul1.csv"
df = pd.read_csv(res_dr, sep=" ")

x = [1000]
for nilai in range(0,kaisuu-1):
    kekka = x[nilai] + x[nilai]
    x.append(kekka)

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