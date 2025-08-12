import bisect
from collections import defaultdict
from itertools import accumulate

N = int(input())
A = map(int, input().split())

ans = 0

for i in range(1, N + 1):
    ans += (N - i + 1) * (i // 2)

D = defaultdict(list)

for i, a in enumerate(A):
    D[a].append(i)

for a in D.keys():
    acc = list(accumulate(D[a], initial=0))

    for ind, i in enumerate(D[a]):
        if ind == 0:
            continue

        bis = bisect.bisect_left(D[a], N - i - 1, hi=ind - 1)

        if bis == ind:
            ans -= acc[ind + 1] + 1
            continue

        if D[a][bis] > N - i - 1:
            bis -= 1

        if D[a][0] > N - i - 1:
            ans -= (ind) * (N - i)
        else:
            ans -= acc[bis + 1]
            ans -= bis + 1
            ans -= (ind - bis - 1) * (N - i)

print(ans)
