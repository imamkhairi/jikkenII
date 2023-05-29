
with open ("output.txt", "r") as f1:
    bun = f1.readlines()

print(bun)
print()
print(bun[1].split(" ")[4])

i = 0
res = []
for sentence in bun:
    if (i == 0): 
        res.append(sentence)
    sentence = sentence.split(" ")
    res.append(sentence[4])
    i += 1
    if (i == 8):
        i = 0
"""
print(res)
