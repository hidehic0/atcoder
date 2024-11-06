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

N, Q = list(map(int, input().split()))
ans = 0
l = 1
r = 2

for _ in [0] * Q:
    H, T = input().split()
    T = int(T)

    if H == "L":
        tl = l
        c = 0
        mode = False
        while tl != T:
            if mode:
                tl -= 1
                c += 1
            else:
                if tl + 1 == r or (tl == N and r == 1):
                    c = 0
                    tl = l
                    mode = True
                else:
                    tl += 1
                    c += 1

            if c > 0:
                if mode:
                    if tl == 0:
                        tl = N
                else:
                    if tl == N + 1:
                        tl = 1

        l = T
        ans += c
    elif H == "R":

        tr = r
        c = 0
        mode = False
        while tr != T:
            if mode:
                tr -= 1
                c += 1
            else:
                if tr + 1 == l or (tr == N and l == 1):
                    c = 0
                    tr = r
                    mode = True
                else:
                    tr += 1
                    c += 1
            if c > 0:
                if mode:
                    if tr == 0:
                        tr = N
                else:
                    if tr == N + 1:
                        tr = 1

        r = T
        ans += c

print(ans)
