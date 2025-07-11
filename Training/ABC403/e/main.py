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

# import pypyjit
# pypyjit.set_param("max_unroll_recursion=-1")

sys.setrecursionlimit(5 * 10**5)
import io
import os
import sys
from typing import Any, List

# インタラクティブ問題の時はIS_INTERACTIVEをTrueにしましょう
# IS_INTERACTIVE = False

# 標準入力関数
# if sys.argv[0] == "Main.py":
#     if not IS_INTERACTIVE:
#         input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline().decode().rstrip


def s() -> str:
    """
    一行に一つのstringをinput
    """
    return input()


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


class RollingHash:
    string: str
    mod: int
    base: int
    n: int

    def __init__(self, string: str, mod: int = (1 << 61) - 1) -> None:
        """
        RollingHash構造体
        衝突する可能性があるのでmodが違う二つで比較するのが有効

        string: 文字列
        mod: mod デフォルト値は2^61 - 1
        """
        self.string = string
        self.mod = mod
        self.base = 29

        self.n = n = len(string)
        self.pow = [1] * (n + 1)
        self.hash = [0] * (n + 1)

        for i in range(n):
            self.hash[i + 1] = (self.hash[i] * self.base + ord(string[i])) % mod

        for i in range(n):
            self.pow[i + 1] = self.pow[i] * self.base % mod

    def get(self, l: int, r: int) -> int:
        """
        lからrまでのハッシュ値を取得する
        0-indexed
        """
        return (self.hash[r] - self.hash[l] * self.pow[r - l]) % self.mod

    def lcp(self, b: int, bn: int) -> int:
        """
        2つのRollingHashの最長共通接頭辞を返す
        bがhashでbnがそのhashの長さです
        """

        left, right = 0, min(self.n, bn)

        while right - left > 1:
            mid = (left + right) // 2

            if self.get(0, mid) == b:
                left = mid
            else:
                right = mid

        return left


# コード
Q = ii()

L = set()
X = set()
Y = defaultdict(set)


while Q:
    T, S = sl()
    hash = RollingHash(S)

    if T == "1":
        h = hash.get(0, len(S))
        for i in Y[h]:
            L.discard(i)

        Y[h].clear()

        X.add(h)
    else:
        flag = False
        for i in range(len(S)):
            if hash.get(0, i + 1) in X:
                flag = True
                break

        if not flag:
            for i in range(len(S)):
                Y[hash.get(0, i + 1)].add(Q)

            L.add(Q)

    print(len(L))

    Q -= 1
