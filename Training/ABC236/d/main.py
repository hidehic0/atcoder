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
import sys
from itertools import permutations
from typing import Any, List


# import pypyjit
#
# pypyjit.set_param("max_unroll_recursion=-1")

sys.setrecursionlimit(5 * 10**5)


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
A = li((N * 2) - 1, il)

ans = 0


def dfs(L, cur):
    global ans

    if len(L) == 0:
        ans = max(ans, cur)
    else:
        b = max(L)
        L.remove(b)
        for i in L:
            T = set([t for t in L])
            a = i
            T.remove(a)

            a, b = min(a, b), max(a, b)

            dfs(T, cur ^ A[a][b - a - 1])


dfs(set(list(range(2 * N))), 0)
print(ans)
