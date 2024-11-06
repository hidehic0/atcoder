# ライブラリと関数と便利変数
# ライブラリ
from collections import deque, defaultdict, Counter
from math import pi
from itertools import permutations
import bisect
import math
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
S = s()

dp = [[-INF] * 3 for _ in [0] * (N)]
dp[0] = [0, 0, 0]

match S[0]:
    case "R":
        dp[0][1] = 1

    case "P":
        dp[0][2] = 1

    case "S":
        dp[0][0] = 1

for i in range(1, N):
    r = max(dp[i - 1][1], dp[i - 1][2])
    p = max(dp[i - 1][0], dp[i - 1][2])
    s = max(dp[i - 1][0], dp[i - 1][1])
    match S[i]:
        case "R":
            dp[i] = [r, max(p + 1, dp[i - 1][1]), s]

        case "P":
            dp[i] = [r, p, max(s + 1, dp[i - 1][2])]

        case "S":
            dp[i] = [max(r + 1, dp[i - 1][0]), p, s]

print(max(dp[-1]))
