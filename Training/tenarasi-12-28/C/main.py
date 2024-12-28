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
from collections import deque, defaultdict, Counter
from math import pi, gcd, lcm
from itertools import permutations
from more_itertools import distinct_permutations
import bisect
import sys
import heapq
from typing import List, Any
import unittest


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


# 便利変数
INF = 1 << 63
lowerlist = list("abcdefghijklmnopqrstuvwxyz")
upperlist = list("ABCDEFGHIJKLMNOPQRSTUVWXYZ")

# コード
N, K = il()
S = list(s())
ans = 0

L = set()

for p in distinct_permutations(S):
    t = 1

    for i in range(N - K + 1):
        flag = True
        for k in range(K // 2):
            if p[i + k] != p[i + K - 1 - k]:
                flag = False
                break

        if flag:
            t = 0
            break
    ans += t

print(ans)
