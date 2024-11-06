# ライブラリと関数と便利変数
# ライブラリ
from collections import deque, defaultdict, Counter
from math import pi
from itertools import permutations
import bisect
import sys
from functools import lru_cache

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
sys.setrecursionlimit(10**6)
H, W, K = il()
L = [list(s()) for _ in [0] * H]
G = [[[] for _ in [0] * W] for _ in [0] * H]

for i in range(H):
    for k in range(W):
        if L[i][k] == "#":
            continue
        try:
            if L[i + 1][k] == ".":
                G[i][k].append((i + 1, k))
        except:
            pass

        try:
            if L[i - 1][k] == ".":
                G[i][k].append((i - 1, k))
        except:
            pass

        try:
            if L[i][k - 1] == ".":
                G[i][k].append((i, k - 1))
        except:
            pass

        try:
            if L[i][k + 1] == ".":
                G[i][k].append((i, k + 1))
        except:
            pass

ans = 0


def dfs(i, k, s):
    global ans
    if len(s) == K + 1:
        ns = []
        for t in s:
            ns.append(t)
        for i in range(1, K):
            if abs(ns[i + 1][0] - ns[i][0]) + abs(ns[i + 1][1] - ns[i][1]) == 1:
                continue
            else:
                break
        else:
            ans += 1
        return

    for dst in G[i][k]:
        if 0 <= dst[0] < H and 0 <= dst[1] < W and dst not in s:
            t = s.copy()
            t.append((i, k))
            dfs(dst[0], dst[1], t)


for i in range(H):
    for k in range(W):
        if L[i][k] == "#":
            continue
        dfs(i, k, [(i, k)])

print(ans)
