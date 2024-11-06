# ライブラリ
def pow(x: int, n: int, t: int = 1):
    if t == 1:
        ans = 1
        while n:
            if n % 2:
                ans = ans * x
            x = x * x
            n >>= 1
        return ans
    ans = 1
    while n:
        if n % 2:
            ans = (ans * x) % t
        x = (x * x) % t
        n >>= 1
    return ans


def is_prime(n: int) -> bool:
    if n == 1:
        return False

    i = 2
    s = n**0.5

    while i < s:
        if n % i == 0:
            return False

        i += 1

    return True


INF = 10**18
lowerlist = list("abcdefghijklmnopqrstuvwxyz")
upperlist = list("ABCDEFGHIJKLMNOPQRSTUVWXYZ")

import bisect

N = int(input())
A = sorted(list(map(int, input().split())))
B = sorted(list(map(int, input().split())))

r = 0

for i in range(N - 1):
    if A[i] <= B[i]:
        continue
    else:
        r += 1

if r >= 1:
    print(-1)
    exit()

ng, ok = (0, A[-1])

while ok - ng > 1:
    mid = (ng + ok) // 2
    TB = B.copy()
    bisect.insort(TB, mid)
    r = 0
    for a, b in zip(A, TB):
        if a <= b:
            continue
        else:
            r += 1
            break

    if r:
        ng = mid
    else:
        ok = mid

print(ng + 1)
