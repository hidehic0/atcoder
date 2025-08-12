from collections import defaultdict

N = int(input())
A = map(int, input().split())

ans = 0

for i in range(1, N + 1):
    ans += (N - i + 1) * (i // 2)

D = defaultdict(list)

for i, a in enumerate(A):
    D[a].append(i)

for a in D.keys():
    t = 0
    for ind, i in enumerate(D[a]):
        for k in range(ind):
            ans -= min(D[a][k] + 1, N - i)
            t += min(D[a][k] + 1, N - i)

    # print(t)


print(ans)
