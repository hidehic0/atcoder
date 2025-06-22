import random

print(10, 100)

for _ in [0] * 100:
    t = random.randrange(1, 4)

    if t == 1:
        print(1, random.randrange(1, 11))
    elif t == 2:
        st = ""

        for _ in [0] * 3:
            st += random.choice(list("abcdefghijklmnopqrstuvwxyz"))

        print(2, random.randrange(1, 11), st)
    else:
        print(3, random.randrange(1, 11))
