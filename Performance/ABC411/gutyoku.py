N, Q = map(int, input().split())

L = [""] * (N + 1)

while Q:
    l = input().split()
    if l[0] == "1":
        L[int(l[1])] = L[0]
    elif l[0] == "2":
        L[int(l[1])] += l[2]
    else:
        L[0] = L[int(l[1])]

    Q -= 1

print(L[0])
