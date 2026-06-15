import itertools

T = int(input())

for _ in [0] * T:
    a, b, c = map(int, input().split())
    N = a + b + c

    ans = [0, []]

    for p in itertools.permutations([0] * a + [1] * b + [2] * c):
        cur = 0

        for i in range(N):
            if p[(i - 1) % N] == p[(i + 1) % N] == (p[i] + 1) % 3:
                cur += 1

        ans = max(ans, [cur, list(p)])

    print(ans)
