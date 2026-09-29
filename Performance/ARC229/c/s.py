from itertools import permutations

for _ in [0] * int(input()):
    N = int(input())
    A = list(map(int, input().split()))

    ans = 1 << 63

    for p in permutations(A):
        cur = 0

        for i in range(N - 1):
            cur += (p[i] + p[i + 1]) // 2

        ans = min(ans, cur)

    print(ans)
