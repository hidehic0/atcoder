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

# sys.setrecursionlimit(5 * 10**5)


# 多次元配列作成
from typing import List, Any


def create_array2(a: int, b: int, default: Any = 0) -> List[List[Any]]:
    """
    ２次元配列を初期化する関数
    """
    return [[default] * b for _ in [0] * a]


def create_array3(a: int, b: int, c: int, default: Any = 0) -> List[List[List[Any]]]:
    """
    ３次元配列を初期化する関数
    """
    return [[[default] * c for _ in [0] * b] for _ in [0] * a]


# 標準入力関数
import sys


def s():
    """
    一行に一つのstringをinput
    """
    return sys.stdin.readline().rstrip()


def sl():
    """
    一行に複数のstringをinput
    """
    return s().split()


def ii():
    """
    一つのint
    """
    return int(s())


def il(add_num: int = 0):
    """
    一行に複数のint
    """
    return list(map(lambda i: int(i) + add_num, sl()))


def li(n: int, func, *args):
    """
    複数行の入力をサポート
    """
    return [func(*args) for _ in [0] * n]


# コード
R, C, K = il()
dp = create_array3(R, C, 5, -(1 << 63))
V = create_array2(R, C, -(1 << 63))


for _ in [0] * K:
    r, c, v = il()
    V[r - 1][c - 1] = v

dp[0][0][0] = 0


for x in range(R):
    for y in range(C):
        for k in reversed(range(3)):
            dp[x][y][k + 1] = max(dp[x][y][k + 1], dp[x][y][k] + V[x][y])

        for k in range(4):
            if dp[x][y][k] < 0:
                continue

            if x + 1 < R:
                dp[x + 1][y][0] = max(dp[x + 1][y][0], dp[x][y][k])

            if y + 1 < C:
                dp[x][y + 1][k] = max(dp[x][y + 1][k], dp[x][y][k])

print(max(dp[-1][-1][:4]))
