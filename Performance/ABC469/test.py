from collections import defaultdict

N, M = map(int, input().split())
C = [0] * N
D = defaultdict(int)

for _ in [0] * M:
    a, b = map(lambda x: int(x) - 1, input().split())
    C[a] += 1
    C[b] += 1

    D[(a, b)] += 1

# xが決勝に上がった回数 + yが決勝に上がった回数 - x,yともに決勝に上がった回数 = Mなら条件を満たす

E = [0] * (M + 1)

ans = 0

for i in range(N)[::-1]:
    ans += E[M - C[i]]
    E[C[i]] += 1

for a, b in D.keys():
    c = D[(a, b)]

    if C[a] + C[b] == M:
        ans -= 1
    if C[a] + C[b] - c == M:
        ans += 1

print(ans)
