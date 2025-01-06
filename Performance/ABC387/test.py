print(1000, 1000)
L = [["."] * 1000 for _ in [0] * 1000]
L[0][0] = "S"
L[-1][-1] = "G"

for line in L:
    print("".join(line))
