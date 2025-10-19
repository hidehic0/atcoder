from math import isqrt

Q = int(input())

for _ in [0] * Q:
    c, d = map(int, input().split())
    ans = 0

    for i in range(1, d + 1):
        a = int(str(c) + str(c + i))
        if a == isqrt(a) ** 2:
            ans += 1

    print(ans)
