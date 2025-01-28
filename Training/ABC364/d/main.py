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

from typing import Callable


def binary_search(fn: Callable[[int], bool], right: int = 0, left: int = -1) -> int:
    """
    二分探索の抽象的なライブラリ
    評価関数の結果に応じて、二分探索する
    最終的にはleftを出力します

    関数のテンプレート
    def check(mid:int):
        if A[mid] > x:
            return True
        else:
            return False

    midは必須です。それ以外はご自由にどうぞ
    """
    while right - left > 1:
        mid = (left + right) // 2

        if fn(mid):
            left = mid
        else:
            right = mid

    return right


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


# 便利変数
INF = 1 << 63
lowerlist = list("abcdefghijklmnopqrstuvwxyz")
upperlist = list("ABCDEFGHIJKLMNOPQRSTUVWXYZ")

# コード
N, Q = il()
A = il()
A.sort()

for _ in [0] * Q:
    B, K = il()

    def c(mid):
        left = bisect.bisect_left(A, B - mid)
        right = bisect.bisect_right(A, B + mid)

        return right - left < K

    print(binary_search(c, 1 << 35, -1))
