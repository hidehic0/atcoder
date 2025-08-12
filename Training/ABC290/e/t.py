import random

n = 15 + random.randint(0, 1)
print(n)
a = []

for _ in [0] * n:
    a.append(random.randint(1, n))

print(*a)
