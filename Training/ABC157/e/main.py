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

from atcoder.segtree import SegTree
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


import math
from typing import Any, Callable, List


class SquareDivision:
    def __init__(self, lis: List[Any], op: Callable[[Any, Any], Any]) -> None:
        self.n = len(lis)
        self.op = op
        self.block_size = math.isqrt(self.n)
        self.blocks = []
        self.lis = lis[:]

        for i in range(0, self.n, self.block_size):
            block_val = lis[i]
            for k in range(i + 1, min(i + self.block_size, self.n)):
                block_val = self.op(block_val, lis[k])
            self.blocks.append(block_val)

        self.m = len(self.blocks)

    def get_block_index_left(self, i: int) -> int:
        return i // self.block_size

    def get_block_index_right(self, i: int) -> int:
        return (i + self.block_size - 1) // self.block_size

    def prod(self, l: int, r: int) -> Any:
        """
        rは0-indexedなのに注意してください
        """
        assert 0 <= l <= r < self.n

        l_block_left = self.get_block_index_left(l)
        r_block_left = self.get_block_index_left(r)

        if l_block_left == r_block_left:
            res = self.lis[l]
            for k in range(l + 1, r + 1):
                res = self.op(res, self.lis[k])
            return res

        res = self.lis[l]
        for i in range(l + 1, min((l_block_left + 1) * self.block_size, self.n)):
            res = self.op(res, self.lis[i])

        for block_ind in range(l_block_left + 1, r_block_left):
            res = self.op(res, self.blocks[block_ind])

        for i in range(r_block_left * self.block_size, r + 1):
            res = self.op(res, self.lis[i])

        return res

    def update(self, i: int, x: Any) -> None:
        assert 0 <= i < self.n
        self.lis[i] = x
        block_ind = self.get_block_index_left(i)
        start = block_ind * self.block_size
        end = min(start + self.block_size, self.n)
        if start < self.n:
            self.blocks[block_ind] = self.lis[start]
            for j in range(start + 1, end):
                self.blocks[block_ind] = self.op(self.blocks[block_ind], self.lis[j])

    def get(self, i: int) -> Any:
        assert 0 <= i < self.n
        return self.lis[i]


N = ii()
S = s()
seg = SegTree(lambda a, b: a.union(b), set(), [{t} for t in S])

Q = ii()

while Q:
    l = sl()

    match l[0]:
        case "1":
            seg.set(int(l[1]) - 1, {l[2]})
        case "2":
            print(len(seg.prod(int(l[1]) - 1, int(l[2]))))

    Q -= 1
