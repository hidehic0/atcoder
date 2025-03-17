import sys
from typing import Any, Callable, List, Tuple


def create_array2(a: int, b: int, default: Any = 0) -> List[List[Any]]:
    """
    2次元配列を初期化する関数
    """
    return [[default] * b for _ in [0] * a]


def binary_search(
    fn: Callable[[int], bool], right: int = 0, left: int = -1, return_left: bool = True
) -> int:
    """
    二分探索の抽象的なライブラリ
    評価関数の結果に応じて、二分探索する
    最終的にはleftを出力します

    関数のテンプレート
    def check(mid:int):
        if A[mid] > x:
            return True
        else:
            return False

    midは必須です。それ以外はご自由にどうぞ
    """
    while right - left > 1:
        mid = (left + right) // 2

        if fn(mid):
            left = mid
        else:
            right = mid

    return left if return_left else right


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
H, W, N = il()
L = create_array2(H + 1, W + 1, 0)

for _ in [0] * N:
    a, b = il()
    L[a][b] += 1

for i in range(H + 1):
    for k in range(1, W + 1):
        L[i][k] += L[i][k - 1]

for k in range(W + 1):
    for i in range(1, H + 1):
        L[i][k] += L[i - 1][k]

ans = 0

for i in range(H):
    for k in range(W):

        def c(mid):
            u, v = i + mid, k + mid

            return (L[u][v] - L[i][v] - L[u][k] + L[i][k]) == 0

        ans += binary_search(c, min(H - i, W - k) + 1, 0)

print(ans)
