r"""
 ______________________
< this is hidehic0's code >
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

┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳
┃                 ┳━━━━┳       ┃
┃    私は人間です ┃ ✔  ┃       ┃
┃                 ┻━━━━┻       ┃
┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┻
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


def manhattan_dis(x1: int, y1: int, x2: int, y2: int) -> int:
    """
    マンハッタン距離を計算します
    """

    return abs(x1 - x2) + abs(y1 - y2)


# 便利変数
INF = 1 << 63
lowerlist = list("abcdefghijklmnopqrstuvwxyz")
upperlist = list("ABCDEFGHIJKLMNOPQRSTUVWXYZ")
MOVES1 = [(0, 1), (0, -1), (1, 0), (-1, 0)]
MOVES2 = MOVES1 + [(1, 1), (1, -1), (-1, 1), (-1, -1)]

# コード
N = ii()
L = li(N, il)
D = defaultdict(int)
T = defaultdict(int)
ans = 0
t = 0


def merge(*args):
    return "a".join([str(t) for t in args])


for i in range(N - 1):
    for k in range(i + 1, N):
        ax, ay = L[i]
        bx, by = L[k]

        if L[i] > L[k]:
            ax, ay = L[k]
            bx, by = L[i]

        dis = manhattan_dis(ax, ay, bx, by)

        bx -= ax
        by -= ay

        gc = gcd(bx, by)
        bx //= gc
        by //= gc

        n = (bx, by)
        ind1 = merge(bx, by)
        ind2 = merge(bx, by, dis)

        ans += D[ind1]
        t += T[ind2]
        D[ind1] += 1
        T[ind2] += 1


print(ans - (t // 2))
