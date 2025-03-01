import random


print(6000, 6000)
L = list("abcdefghijklmnopqrstuvwxyz") + ["a", "o", "i", "?"]

res = ""

for _ in [0] * 6000:
    res += "?"

print(res)

for _ in [0] * 6000:
    print(random.randrange(0, 6000), random.randrange(0, 6000))
