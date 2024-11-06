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
N, S = il()
A = il()
dp = [[False] * (S + 1) for _ in [0] * (N + 1)]
dp[0][0] = True

for i in range(N):
    for k in range(len(dp[0])):
        if dp[i][k]:
            dp[i + 1][k] = dp[i][k]

            try:
                dp[i + 1][k + A[i]] = True
            except:
                pass

if not dp[-1][-1]:
    print(-1)
    exit()

place_i = len(dp) - 1
place_k = len(dp[0]) - 1
ans = []

while True:
    if place_i == 0:
        break

    if dp[place_i - 1][place_k]:
        pass
    else:
        place_k -= A[place_i - 1]
        ans.append(place_i)

    place_i -= 1

print(len(ans))
print(*reversed(ans))
