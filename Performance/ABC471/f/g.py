import random

N = 9
K = random.randint(1, N)

print(N, K)

for _ in [0] * N:
    d = random.randint(0, 10)
    T = str(random.randint(0, 10**d - 1))

    print("0" * random.randint(0, 10 - len(T)) + T)
