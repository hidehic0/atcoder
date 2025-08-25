import random

print(10, 30)
L = set()

for _ in [0] * 30:
    t = random.randint(1, 3)

    if t == 1:
        x = random.randint(1, 9)
        y = random.randint(x + 1, 10)

        while (x, y) in L:
            x = random.randint(1, 9)
            y = random.randint(x + 1, 10)

        L.add((x, y))
        print(1, x, y)
    elif t == 2:
        print(2, random.randint(1, 10))
    else:
        print(3, random.randint(1, 10))
