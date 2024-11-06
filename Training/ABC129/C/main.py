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
mod = 1000000007
N, M = il()
dp = [-1] * (N + 1)

for _ in [0] * M:
    a = ii()
    dp[a] = 0

dp[0] = 1

for i in range(1, N + 1):
    if dp[i] == 0:
        continue
    if i == 1:
        if dp[1] != 0:
            dp[1] = 1

        continue
    elif i == 2:

        if dp[2] != 0:
            if dp[1] == 0:
                dp[2] = 1
            else:
                dp[2] = 2

        continue

    if dp[i - 1] == 0 and dp[i - 2] == 0:
        dp[i] = 0
    elif dp[i - 1] == 0:
        dp[i] = dp[i - 2]
    elif dp[i - 2] == 0:
        dp[i] = dp[i - 1]
    else:
        dp[i] = (dp[i - 1] + dp[i - 2]) % mod

print(dp[N])
