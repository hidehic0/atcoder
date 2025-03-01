r"""
 ______________________
< it's hidehico's code >
 ----------------------
   \
    \
        .--.
       |o_o |
       |:_/ |
      //   \ \
     (|     | )
    /'\_   _/`\
    \___)=(___/
"""

# ライブラリと関数と便利変数
# ライブラリ
import bisect
import copy
import heapq
import math
import sys
from collections import Counter, defaultdict, deque
from itertools import accumulate, combinations, permutations
from math import gcd, lcm, pi
from operator import itemgetter
from typing import Any, List, Tuple

# from atcoder.segtree import SegTree
# from atcoder.lazysegtree import LazySegTree
# from atcoder.dsu import DSU
# cortedcontainersは使うときだけ wandbox非対応なので
# from sortedcontainers import SortedDict, SortedSet, SortedList
import pypyjit

pypyjit.set_param("max_unroll_recursion=-1")

sys.setrecursionlimit(5 * 10**5)


def mod_add(a: int, b: int, mod: int):
    """
    足し算してmodを取った値を出力
    O(1)
    """
    return (a + b) % mod


def mod_sub(a: int, b: int, mod: int):
    """
    引き算してmodを取った値を出力
    O(1)
    """
    return (a - b) % mod


def mod_mul(a: int, b: int, mod: int):
    """
    掛け算してmodを取った値を出力
    O(1)
    """
    return (a * b) % mod


def mod_div(a: int, b: int, mod: int):
    """
    割り算してmodを取った値を出力
    フェルマーの小定理を使って計算します
    O(log mod)
    """
    return (a * pow(b, mod - 2, mod)) % mod


class ModInt:
    def __init__(self, x: int, mod: int = 998244353) -> None:
        self.x = x % mod
        self.mod = mod

    def val(self):
        return self.x

    def rhs(self, rhs) -> int:
        return rhs.x if isinstance(rhs, ModInt) else rhs

    def __add__(self, rhs) -> int:
        return mod_add(self.x, self.rhs(rhs), self.mod)

    def __iadd__(self, rhs) -> "ModInt":
        self.x = self.__add__(rhs)

        return self

    def __sub__(self, rhs) -> int:
        return mod_sub(self.x, self.rhs(rhs), self.mod)

    def __isub__(self, rhs) -> "ModInt":
        self.x = self.__sub__(rhs)

        return self

    def __mul__(self, rhs):
        return mod_mul(self.x, self.rhs(rhs), self.mod)

    def __imul__(self, rhs):
        self.x = self.__mul__(rhs)

        return self

    def __truediv__(self, rhs):
        return mod_div(self.x, self.rhs(rhs), self.mod)

    def __itruediv__(self, rhs):
        self.x = self.__truediv__(rhs)

        return self

    def __floordiv__(self, rhs):
        return (self.x // self.rhs(rhs)) % self.mod

    def __ifloordiv__(self, rhs):
        self.x = self.__floordiv__(rhs)

        return self

    def __pow__(self, rhs):
        return pow(self.x, self.rhs(rhs), self.mod)

    def __eq__(self, rhs) -> bool:
        return self.rhs(rhs) == self.x

    def __ne__(self, rhs) -> bool:
        return self.rhs(rhs) != self.x


# 標準入力関数
import sys
from typing import Any, List


def s() -> str:
    """
    一行に一つのstringをinput
    """
    return sys.stdin.readline().rstrip()


def sl() -> List[str]:
    """
    一行に複数のstringをinput
    """
    return s().split()


def ii() -> int:
    """
    一つのint
    """
    return int(s())


def il(add_num: int = 0) -> List[int]:
    """
    一行に複数のint
    """
    return list(map(lambda i: int(i) + add_num, sl()))


def li(n: int, func, *args) -> List[List[Any]]:
    """
    複数行の入力をサポート
    """
    return [func(*args) for _ in [0] * n]


class Graph:
    """
    グラフ構造体
    """

    def __init__(self, N: int, dire: bool = False) -> None:
        """
        Nは頂点数、direは有向グラフかです
        """
        self.N = N
        self.dire = dire
        self.grath = [[] for _ in [0] * self.N]
        self.in_deg = [0] * N

    def new_side(self, a: int, b: int):
        """
        注意　0-indexedが前提
        aとbを辺で繋ぎます
        有向グラフなら、aからbだけ、無向グラフなら、aからbと、bからaを繋ぎます
        """
        self.grath[a].append(b)
        if self.dire:
            self.in_deg[b] += 1

        if not self.dire:
            self.grath[b].append(a)

    def side_input(self):
        """
        標準入力で、新しい辺を追加します
        """
        a, b = map(lambda x: int(x) - 1, input().split())
        self.new_side(a, b)

    def input(self, M: int):
        """
        標準入力で複数行受け取り、各行の内容で辺を繋ぎます
        """
        for _ in [0] * M:
            self.side_input()

    def get(self, a: int):
        """
        頂点aの隣接頂点を出力します
        """
        return self.grath[a]

    def all(self) -> List[List[int]]:
        """
        グラフの隣接リストをすべて出力します
        """
        return self.grath

    def topological(self, unique: bool = False) -> List[int]:
        """
        トポロジカルソートします
        有向グラフ限定です

        引数のuniqueは、トポロジカルソート結果が、一意に定まらないとエラーを吐きます
        閉路がある、または、uniqueがTrueで一意に定まらなかった時は、[-1]を返します
        """
        if not self.dire:
            raise ValueError("グラフが有向グラフでは有りません (╥﹏╥)")

        in_deg = self.in_deg[:]

        S: deque[int] = deque([])
        order: List[int] = []

        for i in range(self.N):
            if in_deg[i] == 0:
                S.append(i)

        while S:
            if unique and len(S) != 1:
                return [-1]

            cur = S.pop()
            order.append(cur)

            for nxt in self.get(cur):
                in_deg[nxt] -= 1

                if in_deg[nxt] == 0:
                    S.append(nxt)

        if sum(in_deg) > 0:
            return [-1]
        else:
            return [x for x in order]


# コード
N, M = il()
S = s()
G = Graph(N)
G.input(M)

used = [False] * N

ans = ModInt(0)
D = {0: "o", 1: "i"}

hatena_count = S.count("?")


def dfs(cur, turn):
    global ans
    global hatena_count

    if turn == 2:
        ans += 1 * (26**hatena_count)
        return

    for nxt in G.get(cur):
        if used[nxt]:
            continue

        if S[nxt] == D[turn] or S[nxt] == "?":
            if S[nxt] == "?":
                hatena_count -= 1

            used[nxt] = True
            dfs(nxt, turn + 1)
            used[nxt] = False

            if S[nxt] == "?":
                hatena_count += 1


for i in range(N):
    if S[i] == "a" or S[i] == "?":
        if S[i] == "?":
            hatena_count -= 1
        used[i] = True
        dfs(i, 0)
        used[i] = False

        if S[i] == "?":
            hatena_count += 1

print(ans.val())
