from math import gcd

N, K = list(map(int, input().split()))

L = []

G = [0] * (N + 2)
for i in range(1, N + 1)[::-1]:
    G[i] = gcd(G[i + 1], i)

# print(G)
G[N + 1] = 1


def dfs(n, k):
    if n == N:
        if k % n == 0:
            L.append(k // n)
            for i in range(N):
                print(L[i], end="\n" if i == N - 1 else " ")
            L.pop()

        return

    i = 0

    while n * i <= k:
        if (k - n * i) % G[n + 1] == 0:
            L.append(i)
            dfs(n + 1, k - n * i)
            L.pop()

        i += 1


dfs(1, K)
