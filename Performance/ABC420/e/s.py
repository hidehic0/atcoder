N, Q = map(int, input().split())
T = [0] * N
G = [[] for _ in [0] * N]

for _ in [0] * Q:
    l = list(map(int, input().split()))

    if l[0] == 1:
        x, y = l[1:]
        x -= 1
        y -= 1
        G[x].append(y)
        G[y].append(x)
    elif l[0] == 2:
        T[l[1] - 1] ^= 1
    else:
        x = l[1] - 1

        used = [False] * N
        used[x] = True

        S = [x]

        while S:
            cur = S.pop()

            if T[cur]:
                print("Yes")
                break

            for nxt in G[cur]:
                if not used[nxt]:
                    used[nxt] = True
                    S.append(nxt)
        else:
            print("No")
