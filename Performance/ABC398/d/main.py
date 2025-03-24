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
from sortedcontainers import SortedDict, SortedSet, SortedList


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


# コード
N, R, C = il()
S = s()

X = defaultdict(SortedSet)
Y = defaultdict(SortedSet)

X[0].add(0)
Y[0].add(0)

ans = ""

for s in S:
    match s:
        case "N":
            for y in Y.keys():
                for x in Y[y]:
                    Y[y].add(x - 1)
                    Y[y].remove(x)

                    X[x - 1].add(y)
                    X[x].remove(y)

        case "S":
            for y in Y.keys():
                for x in reversed(Y[y]):
                    Y[y].add(x + 1)
                    Y[y].remove(x)

                    X[x + 1].add(y)
                    X[x].remove(y)

        case "W":
            for x in X.keys():
                for y in X[x]:
                    X[x].add(y - 1)
                    X[x].remove(y)

                    Y[y - 1].add(x)
                    Y[y].remove(x)

        case "E":
            for x in X.keys():
                for y in reversed(X[x]):
                    X[x].add(y + 1)
                    X[x].remove(y)

                    Y[y + 1].add(x)
                    Y[y].remove(x)

    ans += "1" if C in X[R] or R in Y[C] else "0"

    X[0].add(0)
    Y[0].add(0)


print(ans)
