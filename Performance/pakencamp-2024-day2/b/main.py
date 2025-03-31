N, K, P = map(int, input().split())
G = [[] for _ in range(N)]
A = [0] * N
for i in range(N - 1):
    u, v = map(int, input().split())
    u -= 1
    v -= 1
    G[u].append(v)
    G[v].append(u)
    A[u] += 1
    A[v] += 1

if N <= 15:
    ans = 0

    for bit in range(1 << N):
        L = [0] * N
        ST = []
        used = [False] * N

        for i in range(N):
            if bit & (1 << i):
                L[i] += 1
                ST.append(i)
                used[i] = True

        while ST:
            cur = ST.pop()
            t = 0

            for nxt in G[cur]:
                t += L[nxt]

                if not used[nxt]:
                    ST.append(nxt)
                    used[nxt] = True

            L[cur] = int(t >= K or L[cur])

        ans += L.count(1)
        ans %= P

    print(ans)
elif K > 2:
    print((N * (2 ** (N - 1))) % P)

else:
    if K == 2:
        if N < 3:
            print((N * (2 ** (N - 1))) % P)
        else:
            print((N * (2 ** (N - 1)) + (N - 2) * (2 ** (N - 3))) % P)
    else:
        if N == 1:
            print(1 % P)
        elif N == 2:
            print(6 % P)
        else:
            print(
                (N * (2 ** (N - 1)) + (N - 2) * 3 * 2 ** (N - 3) + 2 * 2 ** (N - 2)) % P
            )
