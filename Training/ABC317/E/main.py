# ライブラリと関数と便利変数
# ライブラリ
from collections import deque, defaultdict, Counter
from math import pi
from itertools import permutations
import bisect
import sys

# cortedcontainersは使うときだけ wandbox非対応なので
# from sortedcontainers import SortedDict, SortedSet, SortedList


# 関数
def pow(x: int, n: int, t: int = 1):
    # O(log N)
    if t == 1:
        ans = 1
        while n:
            if n % 2:
                ans = ans * x
            x = x * x
            n >>= 1
        return ans
    ans = 1
    while n:
        if n % 2:
            ans = (ans * x) % t
        x = (x * x) % t
        n >>= 1
    return ans


def is_prime(n: int) -> bool:
    # O(√N)
    if n == 1:
        return False

    i = 2
    s = n**0.5

    while i < s:
        if n % i == 0:
            return False

        i += 1

    return True


def gcd(a, b):
    while a > 0 and b > 0:
        if a > b:
            a = a % b
        else:
            b = b % a

    return max(a, b)


def lcm(a, b):
    return (a * b) // gcd(a, b)


# 標準入力系
def s():
    return sys.stdin.readline().rstrip()


def sl():
    return s().split()


def ii():
    return int(s())


def il(add_num: int = 0):
    return list(map(lambda i: int(i) + add_num, sl()))


# 便利変数
INF = 10**18
lowerlist = list("abcdefghijklmnopqrstuvwxyz")
upperlist = list("ABCDEFGHIJKLMNOPQRSTUVWXYZ")

dx = [1, -1, 0, 0]
dy = [0, 0, 1, -1]
# コード
H, W = il()
L = [list(s()) for _ in [0] * H]
sy, sx = -1, -1
gx, gy = -1, -1


HL = []

for i in range(H):
    for k in range(W):
        t = True
        match L[i][k]:
            case ">":
                HL.append((i, k, 2))

            case "v":
                HL.append((i, k, 0))

            case "<":
                HL.append((i, k, 3))

            case "^":
                HL.append((i, k, 1))

            case "S":
                sx, sy = i, k
                t = False

            case "G":
                gx, gy = i, k
                t = False

            case _:
                t = False

        if t:
            L[i][k] = "#"

for i, k, mode in HL:
    i, k = i + dx[mode], k + dy[mode]
    while 0 <= i < H and 0 <= k < W:
        if L[i][k] == "#":
            break

        L[i][k] = "!"
        i, k = i + dx[mode], k + dy[mode]


used = [[-1] * W for _ in [0] * H]
used[sx][sy] = 0
Q = deque()
Q.append((sx, sy))

while Q:
    x, y = Q.popleft()

    for i in range(4):
        nx, ny = x + dx[i], y + dy[i]

        if not (0 <= nx < H and 0 <= ny < W):
            continue

        if L[nx][ny] == "#" or L[nx][ny] == "!":
            continue

        if used[nx][ny] != -1:
            continue

        Q.append((nx, ny))
        used[nx][ny] = used[x][y] + 1

print(used[gx][gy])
