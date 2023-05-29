import subprocess
import sys
import os 

with open("res.txt", "r") as f:
    result = f.readlines()
    
total = 0
for i in range(len(result)):
    result[i] = result[i][0:-1]
    total += float(result[i])
    
print("heikin = {:.6f}".format(total/len(result)))
