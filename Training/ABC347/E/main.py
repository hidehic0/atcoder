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
N, Q = il()
X = il()

D = defaultdict(lambda: -1)
S = set()
ans = [0] * N
A = [0]

for i in range(Q):
    x = X[i]

    if x in S:
        ans[x - 1] += A[-1] - A[D[x]]
        del D[x]
        S.remove(x)
    else:
        D[x] = i
        S.add(x)

    A.append(A[-1] + len(S))

for x in S:
    ans[x - 1] += A[-1] - A[D[x]]

print(*ans)
