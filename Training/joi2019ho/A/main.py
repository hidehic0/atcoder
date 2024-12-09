# ライブラリと関数と便利変数
# ライブラリ
import sys


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
H, W = il()
S = [s() for _ in [0] * H]

OA = [[0] * W for i in range(H)]
IA = [[0] * W for i in range(H)]

for i in range(H):
    for k in range(W - 2, -1, -1):
        OA[i][k] = OA[i][k + 1]

        if S[i][k + 1] == "O":
            OA[i][k] += 1

for i in range(H - 2, -1, -1):
    for k in range(W):
        IA[i][k] = IA[i + 1][k]
        if S[i + 1][k] == "I":
            IA[i][k] += 1

ans = 0

for i in range(H):
    for k in range(W):
        if S[i][k] == "J":
            ans += OA[i][k] * IA[i][k]

print(ans)
