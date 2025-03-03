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
from collections import Counter, defaultdict, deque
from operator import itemgetter
from typing import Any, List, Tuple


def create_array2(a: int, b: int, default: Any = 0) -> List[List[Any]]:
    """
    2次元配列を初期化する関数
    """
    return [[default] * b for _ in [0] * a]


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


# 便利変数
INF = 1 << 63

# コード
N, M, X = map(int, input().split())
A = defaultdict(list)
B = defaultdict(list)

for _ in [0] * M:
    u, v = map(int, input().split())
    u, v = u - 1, v - 1
    A[u].append(v)
    B[v].append(u)

G = [A, B]

used = create_array2(N, 2, INF)
used[0][0] = 0

# cos , cur ,mode
PQ = [(0, 0, 0)]

while PQ:
    cos, cur, mode = heapq.heappop(PQ)

    if used[cur][mode] < cos:
        continue

    if used[cur][mode ^ 1] > cos + X:
        used[cur][mode ^ 1] = cos + X
        heapq.heappush(PQ, (cos + X, cur, mode ^ 1))

    for nxt in G[mode][cur]:
        if used[nxt][mode] > cos + 1:
            used[nxt][mode] = cos + 1
            heapq.heappush(PQ, (cos + 1, nxt, mode))

print(min(used[-1]))
