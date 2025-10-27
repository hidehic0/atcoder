from collections import defaultdict

N, M, C = map(int, input().split())
A = list(map(int, input().split()))

D = defaultdict(int)

for a in A:
    D[a] += 1


ans = 0

for i in range(M):
    cur = i + 1
    cnt = 0

    while cnt < C:
        cnt += D[cur % M]
        cur += 1

    ans += cnt

print(sorted(A))
print(ans)
