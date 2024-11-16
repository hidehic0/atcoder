# ライブラリと関数と便利変数
# ライブラリ
from collections import deque, defaultdict, Counter
from math import pi
from itertools import permutations
import bisect
import sys
import heapq
from typing import List

# cortedcontainersは使うときだけ wandbox非対応なので
# from sortedcontainers import SortedDict, SortedSet, SortedList

sys.setrecursionlimit(5 * 10**5)


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
    # 約数全列挙
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
    # 素因数分解
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
# 一行に一つのstring
def s():
    return sys.stdin.readline().rstrip()


# 一行に複数のstring
def sl():
    return s().split()


# 一つのint
def ii():
    return int(s())


# 一行に複数のint
def il(add_num: int = 0):
    return list(map(lambda i: int(i) + add_num, sl()))


# 複数行の入力をサポート
def li(n: int, func, *args):
    return [func(*args) for _ in [0] * n]


# 自作型
class Heap:
    def __init__(self) -> None:
        self.heap: List[int] = []

    def push(self, x: int):
        """
        値を挿入する関数

        計算量 O(log N)
        Nはheapのサイズ
        """

        # 末尾に挿入
        self.heap.append(x)
        # 現在地の変数
        ind: int = len(self.heap) - 1

        # 更新処理
        while ind > 0:
            # 現在地の親を求める
            # 求め方はセグ木の要領で
            parent: int = (ind - 1) // 2

            # 親の方が小さかったら処理を終了
            if self.heap[parent] <= x:
                break

            # 親より小さかったら入れ替える
            self.heap[ind] = self.heap[parent]
            # 現在地を更新
            ind = parent

        # 最後に現在地にxを代入
        self.heap[ind] = x

    def min(self):
        """
        最小値を出力する関数

        計算量
        O(1)
        """
        if len(self.heap) == 0:
            print("\033[31m error heap is empty \033[0m")
            return
        return self.heap[0]

    def pop(self):
        """
        最小値を削除する関数
        返り値は削除した最小値

        計算量
        N = len(self.heap)
        O(log N)
        """
        # 返り値を取っておく
        result = self.min()

        # self.heapが空ならエラーを吐く
        if len(self.heap) == 0:
            print("\033[31m error heap is empty \033[0m")
            return

        # 末尾の値を取得
        x: int = self.heap.pop()
        # 現在地
        ind = 0

        # 要素がなくなった場合それが最小値なので出力する
        if len(self.heap) == 0:
            return result

        # 更新処理
        while ind * 2 + 1 < len(self.heap):
            # 現在地の子のインデックスを変数に入れとく
            child1 = ind * 2 + 1
            child2 = ind * 2 + 2
            # child2の要素がchild1の要素より小さければchild1をchild2にする
            if child2 < len(self.heap) and self.heap[child2] < self.heap[child1]:
                child1 = child2

            # child1の要素がxより大きければ処理を終了
            if self.heap[child1] >= x:
                break

            # 入れ替え
            self.heap[ind] = self.heap[child1]

            # 現在地を移動
            ind = child1

        # 現在地の要素をxにする
        self.heap[ind] = x

        # 削除した値を返す
        return result


# 無向グラフ
class Graph:
    def __init__(self, N: int, dire: bool = False) -> None:
        self.N = N
        self.dire = dire
        self.grath = [[] for _ in [0] * self.N]

    def new_side(self, a: int, b: int):
        # 注意　0-indexedが前提
        self.grath[a].append(b)
        if not self.dire:
            self.grath[b].append(a)

    def side_input(self):
        # 新しい辺をinput
        a, b = il(-1)
        self.new_side(a, b)

    def input(self, M: int):
        # 複数行の辺のinput
        for _ in [0] * M:
            self.side_input()

    def get(self, a: int):
        # 頂点aの隣接点を出力
        return self.grath[a]

    def all(self):
        # グラフの内容をすべて出力
        return self.grath


# 有向グラフ
class GraphW:
    def __init__(self, N: int, dire: bool = False) -> None:
        self.N = N
        self.dire = dire
        self.grath = [[] for _ in [0] * self.N]

    def new_side(self, a: int, b: int, w: int):
        # 注意　0-indexedが前提
        self.grath[a].append((b, w))
        if not self.dire:
            self.grath[b].append((a, w))

    def side_input(self):
        # 新しい辺をinput
        a, b, w = il(-1)
        self.new_side(a, b, w)

    def input(self, M: int):
        # 複数行の辺のinput
        for _ in [0] * M:
            self.side_input()

    def get(self, a: int):
        # 頂点aの隣接点を出力
        return self.grath[a]

    def all(self):
        # グラフの内容をすべて出力
        return self.grath


# 便利変数
INF = 10**18
lowerlist = list("abcdefghijklmnopqrstuvwxyz")
upperlist = list("ABCDEFGHIJKLMNOPQRSTUVWXYZ")


# テンプレ
class RMAQ:
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

    def query(self, l: int, r: int, a: int, b: int, u: int):
        if r <= a or l >= b:
            return -INF
        if l <= a and b <= r:
            return self.data[u]

        m = (a + b) // 2
        return max(self.query(l, r, a, m, u * 2), self.query(l, r, m, b, u * 2 + 1))


class RMIQ:
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
            self.data[ind] = min(self.data[ind * 2], self.data[ind * 2 + 1])

    def query(self, l: int, r: int, a: int, b: int, u: int):
        if r <= a or l >= b:
            return INF
        if l <= a and b <= r:
            return self.data[u]

        m = (a + b) // 2
        return min(self.query(l, r, a, m, u * 2), self.query(l, r, m, b, u * 2 + 1))


class RSQ:
    def __init__(self, n) -> None:
        self.size = 1
        while self.size < n:
            self.size *= 2

        self.data = [0] * (self.size * 2)

    def update(self, ind, x):
        ind += self.size
        self.data[ind] = x
        while ind >= 2:
            ind //= 2
            self.data[ind] = self.data[ind * 2] + self.data[ind * 2 + 1]

    def query(self, l, r, a, b, u):
        if r <= a or b <= l:
            return 0
        if l <= a and b <= r:
            return self.data[u]
        m = (a + b) // 2

        return self.query(l, r, a, m, u * 2) + self.query(l, r, m, b, u * 2 + 1)


# コード
N, K = il()
S = list(s())
L = []

for i in range(N):
    if S[i] == "1":
        if i == 0:
            L.append([i, i])
        elif S[i - 1] == "0":
            L.append([i, i])
        else:
            L[-1][1] += 1

result = []

for i in range(N):
    if L[K - 2][1] >= i:
        result.append(S[i])
    elif L[K - 2][1] + 1 <= i <= L[K - 2][1] + (L[K - 1][1] - L[K - 1][0]) + 1:
        result.append("1")
    elif L[K - 2][1] + (L[K - 1][1] - L[K - 1][0]) + 2 <= i <= L[K - 1][1]:
        result.append("0")
    else:
        result.append(S[i])

print(*result, sep="")
