import random

N, M = 5, 10
print(N, M)

L = []

for i in range(N):
    for k in range(i + 1, N):
        L.append((i, k))

for u, v in random.sample(L, M):
    print(u + 1, v + 1)
