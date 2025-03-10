import random

N = int(input("いくつ選びますか: "))

L = set()

for _ in [0] * N:
    rn = random.randrange(128, 370)

    while rn in L:
        rn = random.randrange(128, 370)

    print(f"ABC{rn}")
    L.add(rn)
