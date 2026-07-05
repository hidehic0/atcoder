import random

N = 100
print(N)

for _ in [0] * N:
    print(
        "".join([str(random.randrange(0, 10)) for _ in [0] * 6]),
        random.randint(1, 10**9),
    )

Q = 10
print(Q)

for _ in [0] * Q:
    print(
        "".join([str(random.randrange(0, 10)) for _ in [0] * 6]),
        "".join([str(random.randrange(0, 10)) for _ in [0] * 6]),
    )
