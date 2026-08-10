import random

N = 20
P = list(range(1, 2 * N + 1))
random.shuffle(P)

print(N)

for i in range(0, 2 * N, 2):
    if P[i] > P[i + 1]:
        P[i], P[i + 1] = P[i + 1], P[i]

    print(P[i], P[i + 1])
