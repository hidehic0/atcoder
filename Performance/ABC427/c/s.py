N, M = map(int, input().split())
L = []

for _ in [0] * M:
    u, v = map(int, input().split())

    L.append((u - 1, v - 1))

ans = 1 << 63

for bit in range(1 << M):
    G = [[] for _ in [0] * N]
    for i in range(M):
        if bit & (1 << i):
            u, v = L[i]
            G[u].append(v)
            G[v].append(u)

    used = [-1] * N

    for i in range(N):
        if used[i] != -1:
            continue

        Q = [i]

        used[i] = 0

        while Q:
            cur = Q.pop()

            for nxt in G[cur]:
                if used[nxt] == used[cur]:
                    break

                if used[nxt] == -1:
                    used[nxt] = used[cur] ^ 1
                    Q.append(nxt)
            else:
                continue

            break
        else:
            continue

        break
    else:
        ans = min(ans, M - bit.bit_count())

print(ans)
