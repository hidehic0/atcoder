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
import sys
from math import gcd, lcm, pi
from typing import Any

# from atcoder.segtree import SegTree
# from atcoder.lazysegtree import LazySegTree
# from atcoder.fenwicktree import FenwickTree
# from atcoder.dsu import DSU
# cortedcontainersは使うときだけ wandbox非対応なので
# from sortedcontainers import SortedDict, SortedSet, SortedList
import pypyjit

pypyjit.set_param("max_unroll_recursion=-1")

sys.setrecursionlimit(5 * 10**5)
import sys
from typing import Any


def s() -> str:
    """一行に一つのstringをinput"""
    return input()


def sl() -> list[str]:
    """一行に複数のstringをinput"""
    return s().split()


def ii() -> int:
    """一つのint"""
    return int(s())


def il(add_num: int = 0) -> list[int]:
    """一行に複数のint"""
    return list(map(lambda i: int(i) + add_num, sl()))


def li(n: int, func, *args: list[Any]) -> list[list[Any]]:
    """複数行の入力をサポート"""
    return [func(*args) for _ in [0] * n]


from collections.abc import Callable


def rerooting(
    G: list[list[int]],
    merge: Callable[[Any, Any], Any],
    add_root: Callable[[int, Any], Any],
    e,
) -> list[Any]:
    """全方位木dp"""
    _n = len(G)
    dp: list[list[Any]] = [[]] * _n
    ans: list[Any] = [e] * _n

    def _dfs(u: int, p: int = -1):
        nonlocal dp, merge, add_root, e

        res: Any = e
        dp[u] = [e] * (len(G[u]))

        for i, v in enumerate(G[u]):
            if v == p:
                continue

            dp[u][i] = _dfs(v, u)
            res = merge(res, dp[u][i])

        return add_root(u, res)

    def _bfs(u: int, cur: Any, p: int = -1):
        nonlocal dp, merge, add_root, e, ans
        deg = len(G[u])

        for i in range(deg):
            if G[u][i] == p:
                dp[u][i] = cur

        dp_l, dp_r = [e] * (deg + 1), [e] * (deg + 1)

        for i in range(deg):
            dp_l[i + 1] = merge(dp_l[i], dp[u][i])

        for i in reversed(range(deg)):
            dp_r[i] = merge(dp_r[i + 1], dp[u][i])

        ans[u] = add_root(u, dp_l[deg])

        for i in range(deg):
            if G[u][i] != p:
                _bfs(G[u][i], add_root(u, merge(dp_l[i], dp_r[i + 1])), u)

    _dfs(0)
    _bfs(0, e)

    return ans


# 便利変数
INF = 1 << 63
lowerlist = list("abcdefghijklmnopqrstuvwxyz")
upperlist = list("ABCDEFGHIJKLMNOPQRSTUVWXYZ")
MOVES1 = [(0, 1), (0, -1), (1, 0), (-1, 0)]
MOVES2 = MOVES1 + [(1, 1), (1, -1), (-1, 1), (-1, -1)]

# コード
N = ii()
G = [[] for _ in [0] * N]

for _ in [0] * (N - 1):
    a, b = il(-1)
    G[a].append(b)
    G[b].append(a)


def add_root(p, a):
    m = max((0, p), a)
    return m[0] + 1, m[1]


print(*[b + 1 for a, b in rerooting(G, max, add_root, (-INF, -INF))], sep="\n")
