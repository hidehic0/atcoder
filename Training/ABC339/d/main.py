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


def coordinate_check(x: int, y: int, H: int, W: int) -> bool:
    """
    座標がグリッドの範囲内にあるかチェックする関数
    0-indexedが前提
    """

    return 0 <= x < H and 0 <= y < W


# 便利変数
INF = 1 << 63
lowerlist = list("abcdefghijklmnopqrstuvwxyz")
upperlist = list("ABCDEFGHIJKLMNOPQRSTUVWXYZ")

# コード
N = ii()
S = li(N, s)

px1, py1, px2, py2 = -1, -1, -1, -1

for i in range(N):
    for k in range(N):
        if S[i][k] != "P":
            continue

        if px1 == -1 and py1 == -1:
            px1, py1 = i, k
        else:
            px2, py2 = i, k

used = [create_array3(N, N, N, INF) for _ in [0] * N]
used[px1][py1][px2][py2] = 0
Q = deque()
Q.append((px1, py1, px2, py2))

while Q:
    x1, y1, x2, y2 = Q.popleft()
    if x1 == x2 and y1 == y2:
        print(used[x1][y1][x2][y2])
        exit()

    for mx, my in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
        nx1, ny1 = x1 + mx, y1 + my
        nx2, ny2 = x2 + mx, y2 + my

        if (not coordinate_check(nx1, ny1, N, N)) or S[nx1][ny1] == "#":
            nx1, ny1 = x1, y1

        if (not coordinate_check(nx2, ny2, N, N)) or S[nx2][ny2] == "#":
            nx2, ny2 = x2, y2

        if used[nx1][ny1][nx2][ny2] != INF:
            continue

        used[nx1][ny1][nx2][ny2] = used[x1][y1][x2][y2] + 1
        Q.append((nx1, ny1, nx2, ny2))


print(-1)
