from collections import defaultdict

N, Q = list(map(int, input().split()))
D = defaultdict(int)
A = [0] * N
D[0] = N

cur = 0
offset = 0

for _ in [0] * Q:
    l = list(map(int, input().split()))
    if l[0] == 1:
        x = l[1] - 1

        t = max(0, A[x] - offset)
        assert D[t]

        cur ^= t
        cur ^= t + 1

        D[t] -= 1
        D[t + 1] += 1
        A[x] += 1
    else:
        offset += 1
        ND = defaultdict(int)
        ND[0] = D[0]

        for k, v in D.items():
            if k == 0:
                continue

            ND[k - 1] += D[k]

            if v % 2 != 0:
                cur ^= k ^ (k - 1)

        D = ND

    print(cur)
