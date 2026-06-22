import bisect

INF = 10**15

N, K = list(map(int, input().split()))
L = [list(map(int, input().split())) for _ in [0] * N]

V = [-INF]

for l, r in L:
    V.append(l)
    V.append(r)

V = sorted(set(V))
R = [[] for _ in [0] * len(V)]

for l, r in L:
    R[bisect.bisect_left(V, r)].append(l)

left, right = -1, 10**9

while right - left > 1:
    mid = (left + right) >> 1
    dp = [-INF] * len(V)
    dp[0] = 0

    for i in range(1, len(V)):
        dp[i] = max(dp[i], dp[i - 1])

        for l in R[i]:
            dp[i] = max(dp[i], dp[bisect.bisect_right(V, l - mid) - 1] + 1)

    if dp[-1] >= K:
        left = mid
    else:
        right = mid

if left <= 0:
    print(-1)
else:
    print(left)
