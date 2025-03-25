// Original Python code:
/*
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
# from sortedcontainers import SortedDict, SortedSet, SortedList

import pypyjit

pypyjit.set_param("max_unroll_recursion=-1")


def create_array1(n: int, default: Any = 0) -> List[Any]:
    """
    1次元配列を初期化する関数
    """
    return [default] * n


def create_array2(a: int, b: int, default: Any = 0) -> List[List[Any]]:
    """
    2次元配列を初期化する関数
    """
    return [[default] * b for _ in [0] * a]


def create_array3(a: int, b: int, c: int, default: Any = 0) -> List[List[List[Any]]]:
    """
    3次元配列を初期化する関数
    """
    return [[[default] * c for _ in [0] * b] for _ in [0] * a]


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


def coordinate_check(x: int, y: int, H: int, W: int) -> bool:
    """
    座標がグリッドの範囲内にあるかチェックする関数
    0-indexedが前提
    """

    return 0 <= x < H and 0 <= y < W


from typing import List, Tuple


def grid_moves(
    x: int,
    y: int,
    H: int,
    W: int,
    moves: List[Tuple[int]] = [(0, 1), (0, -1), (1, 0), (-1, 0)],
    *check_funcs,
) -> List[Tuple[int]]:
    """
    現在の座標から、移動可能な座標をmovesをもとに列挙します。
    xとyは現在の座標
    HとWはグリッドのサイズ
    movesは移動する座標がいくつかを保存する
    check_funcsは、その座標の点が#だとかを自前で実装して判定はこちらでするみたいな感じ
    なおcheck_funcsは引数がxとyだけというのが条件
    追加の判定関数は、弾く場合は、False それ以外ならTrueで
    """
    res = []

    for mx, my in moves:
        nx, ny = x + mx, y + my

        if not coordinate_check(nx, ny, H, W):
            continue

        for f in check_funcs:
            if not f(nx, ny):
                break
        else:
            res.append((nx, ny))

    return res


# コード
H, W, K = il()
S = li(H, s)

ans = 0

MOVES = [(0, 1), (0, -1), (1, 0), (-1, 0)]

used = create_array2(H, W, False)


def dfs(x, y, k):
    global ans

    if k == K:
        ans += 1
        return

    for nx, ny in grid_moves(
        x, y, H, W, MOVES, lambda x, y: S[x][y] == ".", lambda x, y: not used[x][y]
    ):
        used[nx][ny] = True
        dfs(nx, ny, k + 1)
        used[nx][ny] = False


for x in range(H):
    for y in range(W):
        if S[x][y] == "#":
            continue

        used = create_array2(H, W, False)
        used[x][y] = True
        dfs(x, y, 0)

print(ans)
*/

#include <bits/stdc++.h>
using namespace std;

// Global variables
int H, W, K;
vector<string> S;
int ans = 0;
vector<pair<int, int>> MOVES = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

// 2D array creation
vector<vector<bool>> create_array2(int a, int b, bool default_val = false) {
    return vector<vector<bool>>(a, vector<bool>(b, default_val));
}

// Coordinate check
bool coordinate_check(int x, int y, int H, int W) {
    return 0 <= x && x < H && 0 <= y && y < W;
}

// Global used array (will be reinitialized in the main loop)
vector<vector<bool>> used;

// Grid moves function
vector<pair<int, int>> grid_moves(int x, int y, int H, int W, vector<pair<int, int>> moves) {
    vector<pair<int, int>> res;
    for (auto [mx, my] : moves) {
        int nx = x + mx;
        int ny = y + my;

        if (!coordinate_check(nx, ny, H, W)) {
            continue;
        }

        // Check conditions: S[x][y] == "." and not used[x][y]
        if (S[nx][ny] == '.' && !used[nx][ny]) {
            res.push_back({nx, ny});
        }
    }
    return res;
}


// DFS function
void dfs(int x, int y, int k) {
    if (k == K) {
        ans++;
        return;
    }

    for (auto [nx, ny] : grid_moves(x, y, H, W, MOVES)) {
        used[nx][ny] = true;
        dfs(nx, ny, k + 1);
        used[nx][ny] = false;
    }
}

int main() {
    // Input
    cin >> H >> W >> K;
    S.resize(H);
    for (int i = 0; i < H; i++) {
        cin >> S[i];
    }

    // Main logic
    for (int x = 0; x < H; x++) {
        for (int y = 0; y < W; y++) {
            if (S[x][y] == '#') {
                continue;
            }

            used = create_array2(H, W, false);
            used[x][y] = true;
            dfs(x, y, 0);
        }
    }

    cout << ans << endl;
    return 0;
}
