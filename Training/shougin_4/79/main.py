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
import heapq
import sys
import unittest
from collections import Counter, defaultdict, deque
from itertools import permutations
from math import gcd, lcm, pi
from typing import Any, List

# from atcoder.segtree import SegTree
# from atcoder.lazysegtree import LazySegTree
# from atcoder.dsu import DSU

# cortedcontainersは使うときだけ wandbox非対応なので
# from sortedcontainers import SortedDict, SortedSet, SortedList

# import pypyjit
# pypyjit.set_param("max_unroll_recursion=-1")


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


# 便利変数
INF = 1 << 63
lowerlist = list("abcdefghijklmnopqrstuvwxyz")
upperlist = list("ABCDEFGHIJKLMNOPQRSTUVWXYZ")

# コード
N, M, K = il()
G = Graph(N)
G.input(M)

PQ = []
used = [-INF] * N

for _ in [0] * K:
    p, h = il()
    p -= 1

    used[p] = h
    heapq.heappush(PQ, (-h, p))

while PQ:
    h, cur = heapq.heappop(PQ)
    h *= -1

    if used[cur] != h:
        continue

    if h <= 0:
        continue

    h -= 1

    for nxt in G.get(cur):
        if used[nxt] < h:
            used[nxt] = h

            heapq.heappush(PQ, (-h, nxt))

ans = []

for i in range(N):
    if used[i] >= 0:
        ans.append(i + 1)

print(len(ans))
print(*ans)
