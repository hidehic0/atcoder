# ライブラリと関数と便利変数
# ライブラリ
import sys
from collections import deque
from typing import Any, List


def create_array3(a: int, b: int, c: int, default: Any = 0) -> List[List[List[Any]]]:
    """
    ３次元配列を初期化する関数
    """
    return [[[default] * c for _ in [0] * b] for _ in [0] * a]


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


def coordinate_check(x: int, y: int, H: int, W: int) -> bool:
    """
    座標がグリッドの範囲内にあるかチェックする関数
    0-indexedが前提
    """

    return 0 <= x < H and 0 <= y < W


# 便利変数
INF = 1 << 30

# コード
H, W = il()
MOVES = [(0, 1), (0, -1), (1, 0), (-1, 0)]
sx, sy = il(-1)
gx, gy = il(-1)
S = li(H, s)

used = create_array3(H, W, 4, INF)
used[sx][sy] = [0, 0, 0, 0]

Q = deque()

for i in range(4):
    Q.append((sx, sy, i))

while Q:
    x, y, mode = Q.popleft()

    for i in range(4):
        nx, ny = x + MOVES[i][0], y + MOVES[i][1]

        if not coordinate_check(nx, ny, H, W):
            continue

        if S[nx][ny] == "#":
            continue

        t = 0 if i == mode else 1

        if used[nx][ny][i] > used[x][y][mode] + t:
            used[nx][ny][i] = used[x][y][mode] + t

            if t:
                Q.append((nx, ny, i))
            else:
                Q.appendleft((nx, ny, i))

print(min(used[gx][gy]))
