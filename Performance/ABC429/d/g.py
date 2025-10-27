import random

M = 10
print(10, M, random.randint(0, 10))
print(*[random.randint(0, M - 1) for _ in [0] * 10])
