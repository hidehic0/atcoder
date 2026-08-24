from itertools import combinations, permutations

N, K = map(int, input().split())
S = [input() for _ in [0] * N]

ans = 0

for c in combinations(S, K):
    for p in permutations(c):
        ans = max(ans, int("".join(p)))

print(ans)
