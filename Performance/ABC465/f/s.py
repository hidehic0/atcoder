N = int(input())
L = []

for _ in [0] * N:
    L.append(input().split())

for _ in [0] * int(input()):
    x, y = input().split()

    ans = 0

    for s, v in L:
        for i in range(6):
            if not int(x[i]) <= int(str(s)[i]) <= int(y[i]):
                break
        else:
            ans += int(v)

    print(ans)
