#!/usr/bin/env pypy3
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
from collections import defaultdict
import heapq


# 標準入力系
# 一行に一つのstring
def s():
    return sys.stdin.readline().rstrip()


# 一行に複数のstring
def sl():
    return s().split()


# 一つのint
def ii():
    return int(s())


# 一行に複数のint
def il(add_num: int = 0):
    return list(map(lambda i: int(i) + add_num, sl()))


# 複数行の入力をサポート
def li(n: int, func, *args):
    return [func(*args) for _ in [0] * n]


# コード
N = ii()
DF = defaultdict(int)
PQ = []

for _ in [0] * N:
    S, C = il()
    DF[S] += C
    heapq.heappush(PQ, S)

while PQ:
    cur = heapq.heappop(PQ)
    DF[cur * 2] += DF[cur] // 2
    DF[cur] %= 2

    if DF[cur * 2] >= 2:
        heapq.heappush(PQ, cur * 2)

print(sum(DF.values()))
