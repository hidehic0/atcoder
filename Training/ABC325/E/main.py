# ライブラリと関数と便利変数
# ライブラリ
from collections import deque, defaultdict, Counter
from math import pi
from itertools import permutations
import bisect
import sys
import heapq


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
INF = 1 << 63 - 1
lowerlist = list("abcdefghijklmnopqrstuvwxyz")
upperlist = list("ABCDEFGHIJKLMNOPQRSTUVWXYZ")


# コード
N, A, B, C = il()
D = [il() for _ in [0] * N]

used1 = [INF] * N
used1[0] = 0
PQ = [(0, 0)]

while PQ:
    cost, cur = heapq.heappop(PQ)
    if used1[cur] < cost:
        continue

    for next in range(N):
        nco = cost + D[cur][next] * A

        if used1[next] > nco:
            heapq.heappush(PQ, (nco, next))
            used1[next] = nco


used2 = [INF] * N
used2[N - 1] = 0
PQ = [(0, N - 1)]

while PQ:
    cost, cur = heapq.heappop(PQ)

    if used2[cur] < cost:
        continue

    for next in range(N):
        nco = cost + D[cur][next] * B + C

        if used2[next] > nco:
            heapq.heappush(PQ, (nco, next))
            used2[next] = nco

ans = INF

for i in range(N):
    ans = min(ans, used1[i] + used2[i])

print(ans)
