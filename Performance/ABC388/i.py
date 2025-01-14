import random

print(300)
L = []

for _ in [0] * 300:
    L.append(random.randint(1, 10**9))

print(*sorted(L))
