import random

from atcoder.dsu import DSU

N = 5
print(N)
UF = DSU(N)
E = []

while len(E) < N - 1:
    a = random.randint(0, N - 2)
    b = random.randint(a + 1, N - 1)

    if not UF.same(a, b):
        print(a + 1, b + 1)
        UF.merge(a, b)
        E.append((a, b))
