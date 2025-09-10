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
from atcoder.fenwicktree import FenwickTree

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


from typing import Callable


def binary_search(
    fn: Callable[[int], bool], right: int = 0, left: int = -1, return_left: bool = True
) -> int:
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

    return left if return_left else right


def compress_1d(points: List[int] | Tuple[int]) -> List[int]:
    """
    一次元座標圧縮します
    計算量は、O(N log N)です

    lとrは、まとめて入れる事で、座圧できます
    """
    res = []
    d = {num: ind for ind, num in enumerate(sorted(set(points)))}

    for a in points:
        res.append(d[a])

    return d


# コード
N = ii()
L = li(N, il)
L.sort(key=lambda x: x[0])
Y = [x[1] for x in L]
Y.sort()

y_map = compress_1d([x[1] for x in L])


def f(k):
    ft = FenwickTree(N)

    cur = 0

    for i in range(1, N):
        while cur < i and L[i][0] - L[cur][0] >= k:
            ft.add(y_map[L[cur][1]], 1)
            cur += 1

        bis_a = bisect.bisect_left(Y, L[i][1] + k)
        a = None
        if bis_a >= N:
            a = -1
        else:
            a = ft.sum(y_map[Y[bis_a]], N)

        bis_b = bisect.bisect_right(Y, L[i][1] - k) - 1
        b = None

        if abs(L[i][1] - Y[bis_b]) >= k:
            b = ft.sum(0, y_map[Y[bis_b]] + 1)
        else:
            b = -1

        if b >= 1 or a >= 1:
            return True

    return False


print(binary_search(f, min(Y[-1] - Y[0], L[-1][0] - L[0][0]) + 1, 0))
