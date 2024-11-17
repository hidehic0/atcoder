import random

print(50, 5)
A = []

for _ in [0] * 50:
    A.append(random.randint(1, 50))

print(*A)
