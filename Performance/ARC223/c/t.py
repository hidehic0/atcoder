import random

N = 1000
print(1)
print(N)
print(*[random.randint(1, 10**9) for _ in [0] * N])
