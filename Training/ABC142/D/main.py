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


def eratosthenes(n):
    primes = [True] * (n + 1)
    primes[0], primes[1] = False, False
    i = 2
    while i**2 <= n:
        if primes[i]:
            for k in range(i * 2, n + 1, i):
                primes[k] = False

        i += 1

    return [i for i, p in enumerate(primes) if p]


def gcd(a, b):
    while a > 0 and b > 0:
        if a > b:
            a = a % b
        else:
            b = b % a

    return max(a, b)


def lcm(a, b):
    return (a * b) // gcd(a, b)


def calc_divisors(N):
    result = []

    for i in range(1, N + 1):
        if i * i > N:
            break

        if N % i != 0:
            continue

        heapq.heappush(result, i)
        if N // i != i:
            heapq.heappush(result, N // i)

    return result


def factorization(n):
    result = []
    tmp = n
    for i in range(2, int(-(-(n**0.5) // 1)) + 1):
        if tmp % i == 0:
            cnt = 0
            while tmp % i == 0:
                cnt += 1
                tmp //= i
            result.append([i, cnt])

    if tmp != 1:
        result.append([tmp, 1])

    if result == []:
        result.append([n, 1])

    return result


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


# テンプレ
class SegmentTree:
    # 鉄則本のパクリですけどよろしく
    def __init__(self, N) -> None:
        # サイズは要素の数

        self.size = 1
        while self.size < N:
            self.size *= 2

        self.data = [0] * (self.size * 2)

    def update(self, ind, x):
        ind = ind + self.size - 1
        self.data[ind] = x

        while ind >= 2:
            ind //= 2
            self.data[ind] = max(self.data[ind * 2], self.data[ind * 2 + 1])

    def query(self, l, r, a, b, u):
        if r <= a or l >= b:
            return -INF
        if l <= a and b <= r:
            return self.data[u]

        m = (a + b) // 2
        return max(self.query(l, r, a, m, u * 2), self.query(l, r, m, b, u * 2 + 1))


# コード
A, B = il()
ans = 0

C = gcd(A, B)
S = set()

for d in calc_divisors(C):
    if all([gcd(d, s) == 1 for s in S]):
        S.add(d)
        ans += 1

print(ans)
