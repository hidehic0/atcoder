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

# コード
(
    N,
    C,
) = list(map(int, input().split()))
A = list(map(int, input().split()))
r = 1
t = A[0]

for i in A[1:]:
    if i - t >= C:
        r += 1
        t = i

print(r)
