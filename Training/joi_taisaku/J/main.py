# ライブラリと関数と便利変数
# ライブラリ
import bisect
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
N, M = il()
P = li(N, ii)
L = P.copy()

for i in range(N):
    for k in range(N):
        L.append(P[i] + P[k])

L.sort()
ans = 0
for s in L:
    bis = bisect.bisect_right(L, M - s)

    if bis == 0:
        continue
    bis -= 1

    ans = max(ans, L[bis] + s)

print(ans)
