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
N = ii()
L = []
T = []
ans = 0

for _ in [0] * N:
    A = il()
    D = defaultdict(int)
    nt = set()

    for a in A[1:]:
        nt.add(a)
        D[a] += 1

    for t in D.keys():
        D[t] = D[t] / A[0]

    L.append(D)
    T.append(list(nt))

for i in range(N):
    for k in range(i + 1, N):
        cur = 0
        for t in T[k]:
            cur += L[i][t] * L[k][t]

        ans = max(ans, cur)

print(ans)
