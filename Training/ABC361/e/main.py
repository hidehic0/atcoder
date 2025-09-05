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
# from atcoder.fenwicktree import FenwickTree
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


def eratosthenes(n: int) -> List[int]:
    """
    n以下の素数を列挙します
    計算量は、O(n log log n)です
    先程の素数判定法で列挙するよりも、少し速いです
    列挙した素数は昇順に並んでいます
    アルゴリズムはエラトステネスです
    """
    primes = [True] * (n + 1)
    primes[0], primes[1] = False, False
    i = 2
    while i**2 <= n:
        if primes[i]:
            for k in range(i * 2, n + 1, i):
                primes[k] = False

        i += 1

    return [i for i, p in enumerate(primes) if p]


def factorization_plural(L: List[int]) -> List[List[List[int]]]:
    """
    複数の数の素因数分解を行ないます
    計算量は、O(N * (√max(L) log log √max(L)))
    みたいな感じです

    最初に素数を列挙するため、普通の素因数分解より効率がいいです
    """
    res = []
    primes = eratosthenes(int(max(L) ** 0.5) + 20)

    def solve(n):
        t = []
        for p in primes:
            if n % p == 0:
                cnt = 0
                while n % p == 0:
                    cnt += 1
                    n //= p

                t.append([p, cnt])

        if n != 1:
            t.append([n, 1])

        if t == []:
            t.append([n, 1])

        return t

    for n in L:
        res.append(solve(n))

    return res


# コード
N = int(input())

ans = math.isqrt(N)

L = eratosthenes(60)
FL = factorization_plural(range(1, 10**6 + 2))

for b in range(3, 62):
    if b not in L or 2**b > N:
        continue

    i = 2

    while i**b <= N:
        l = FL[i - 1]
        l = [[t[0], t[1] * b] for t in l]

        for i in range(2, b):
            flag = True
            for t in l:
                if t[1] % i != 0:
                    flag = False
                    break

            if flag:
                break
        else:
            ans += 1
            i += 1

print(ans)
