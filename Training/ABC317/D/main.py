# ライブラリと関数と便利変数
# ライブラリ
from collections import deque, defaultdict, Counter
from math import pi
from itertools import permutations
import bisect
import sys

# cortedcontainersは使うときだけ wandbox非対応なので
# from sortedcontainers import SortedDict, SortedSet, SortedList


# 関数
def pow(x: int, n: int, t: int = 1):
    # O(log N)
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
    # O(√N)
    if n == 1:
        return False

    i = 2
    s = n**0.5

    while i < s:
        if n % i == 0:
            return False

        i += 1

    return True


def gcd(a, b):
    while a > 0 and b > 0:
        if a > b:
            a = a % b
        else:
            b = b % a

    return max(a, b)


def lcm(a, b):
    return (a * b) // gcd(a, b)


# 標準入力系
def s():
    return sys.stdin.readline().rstrip()


def sl():
    return s().split()


def ii():
    return int(s())


def il(add_num: int = 0):
    return list(map(lambda i: int(i) + add_num, sl()))


# 便利変数
INF = 10**18
lowerlist = list("abcdefghijklmnopqrstuvwxyz")
upperlist = list("ABCDEFGHIJKLMNOPQRSTUVWXYZ")


# コード
N = ii()
rn = 0
sumz = 0
L = []

for _ in [0] * N:
    x, y, z = il()

    if x > y:
        rn += z
    else:
        L.append((x, y, z))

    sumz += z

dp = [[INF] * (sumz + 1) for _ in [0] * (len(L) + 1)]

dp[0][rn] = 0


def change_people_required(x, y):
    return ((x + y) // 2 + 1) - x


for i in range(1, len(L) + 1):
    x, y, z = L[i - 1]

    for k in range(len(dp[0])):
        try:
            dp[i][k] = min(dp[i][k], dp[i - 1][k])
            if dp[i][k] == INF:
                continue

            dp[i][k + z] = min(
                dp[i][k + z], dp[i - 1][k] + change_people_required(x, y)
            )
        except:
            pass

ans = INF
t = sumz // 2 + 1

for l in dp:
    ans = min(min(l[t:]), ans)

print(ans)
