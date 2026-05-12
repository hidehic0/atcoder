# Segment Tree for codon
# https://github.com/navel-tos/cp-library-for-codon/blob/main/algorithm/segment_tree/segment_tree.py
class SegTree[T, F]:
    """
    Segment Tree for codon
    配列の一点更新・区間積取得を行います。

    op: 二項演算  op(node_Lt: T, node_Rt: T) -> node_new: T
    e: 単位元  配列の要素と同じ型Tにしてください
    N: 配列の長さ  第3引数にN: intを渡す場合、配列は単位元eで初期化します
    A: 初期化に用いる長さNの配列
    """

    _N: int
    _logN: int
    _size: int
    _node: list[T]
    _f: F
    _e: T
    __slots__ = ("_N", "_logN", "_size", "_node", "_f", "_e")

    def __init__(self, op: F, e: T, N: int) -> None:
        self._N = N
        self._logN = 64 - max(0, self._N - 1).__ctlz__()  # max(0, N - 1).bit_length()
        self._size = 1 << self._logN
        self._f, self._e = op, e
        self._node = [self._e for _ in range(self._size << 1)]

    def __init__(self, op: F, e: T, A: generator[T]) -> None:
        self.__init__(op, e, list(A))  # len(A)が分からないのでlistにキャスト

    def __init__(self, op: F, e: T, A: list[T]) -> None:
        self.__init__(op, e, len(A))
        for i, Ai in enumerate(A, start=self._size):
            self._node[i] = Ai
        for i in range(self._size - 1, 0, -1):
            self._node[i] = self._f(self._node[i << 1], self._node[i << 1 | 1])

    # 基本機能: 更新・取得
    def set(self, i: int, value: T) -> None:
        "A[i]の値をvalueに変更します。"
        assert 0 <= i < self._N
        i |= self._size
        self._node[i] = value
        while i := i >> 1:
            self._node[i] = self._f(self._node[i << 1], self._node[i << 1 | 1])

    def get(self, i: int) -> T:
        "時間計算量O(1)で、A[i]の値を取得します。"
        assert 0 <= i < self._N
        return self._node[i | self._size]

    def prod(self, Lt: int, Rt: int) -> T:
        """
        半開区間A[Lt, Rt)の積を返します。A[Rt]は含みません。
        Lt == Rt の場合、単位元eを返します。
        """
        assert 0 <= Lt <= Rt <= self._N
        if Lt == Rt:
            return self._e
        Lt, Rt = Lt | self._size, Rt + self._size
        vL, vR = self._e, self._e
        while Lt < Rt:
            if Lt & 1:
                vL = self._f(vL, self._node[Lt])
                Lt += 1
            if Rt & 1:
                Rt ^= 1
                vR = self._f(self._node[Rt], vR)
            Lt >>= 1
            Rt >>= 1
        return self._f(vL, vR)

    def all_prod(self) -> T:
        "時間計算量O(1)で、A[0, N)の全区間積を返します。"
        return self._node[1] if self._N != 0 else self._e

    # セグメント木内の二分探索
    def max_right(self, Lt: int, judge: Function[tuple[T], bool]) -> int:
        """
        区間積の単調性を仮定します。
        半開区間の左端Lt(0 <= Lt <= N)と、判定関数 judge(区間積: T) -> bool を渡します。
        ただし、 judge(単位元e) == True を要求します。
        judge(半開区間積A[Lt, Rt)) == True を満たす最大のRt(Lt <= Rt <= N)を返します。
        """
        assert 0 <= Lt <= self._N
        if Lt == self._N:
            return self._N
        i, cnt = Lt | self._size, self._e
        while True:
            t = self._f(cnt, self._node[i])
            if judge(t):
                if i & 1:
                    cnt = t
                    i += 1
                    if (i - 1) & i == 0:
                        return self._N
                i >>= 1
            else:
                break
        while i < self._size:
            i <<= 1
            t = self._f(cnt, self._node[i])
            if judge(t):
                cnt = t
                i |= 1
        return i ^ self._size

    def min_left(self, Rt: int, judge: Function[tuple[T], bool]) -> int:
        """
        区間積の単調性を仮定します。
        半開区間の右端Rt(0 <= Rt <= N)と、判定関数 judge(区間積: T) -> bool を渡します。
        ただし、 judge(単位元e) == True を要求します。
        judge(半開区間積A[Lt, Rt)) == True を満たす最小のLt(0 <= Lt <= Rt)を返します。
        """
        assert 0 <= Rt <= self._N
        if Rt == 0:
            return 0
        i, cnt = (Rt - 1) | self._size, self._e
        while i:
            t = self._f(self._node[i], cnt)
            if judge(t):
                if i & 1 == 0:
                    cnt = t
                    i -= 1
                    if i & (i + 1) == 0:
                        return 0
                i >>= 1
            else:
                break
        if i == 0:
            return 0
        while i < self._size:
            i = i << 1 | 1
            t = self._f(self._node[i], cnt)
            if judge(t):
                cnt = t
                i ^= 1
        return (i ^ self._size) + 1


T = int(input())


def create_array1(n: int, default=0):
    """1次元配列を初期化する関数"""
    return [default] * n


def create_array2(a: int, b: int, default=0):
    """2次元配列を初期化する関数"""
    return [[default] * b for _ in [0] * a]


def create_array3(a: int, b: int, c: int, default=0):
    """3次元配列を初期化する関数"""
    return [[[default] * c for _ in [0] * b] for _ in [0] * a]


INF = 10**18


def mat_mul(
    a: list[list[int]],
    b: list[list[int]],
) -> list[list[int]]:
    """行列の積"""
    res = [[INF] * len(b[0]) for _ in [0] * len(a)]

    for i in range(len(a)):
        for j in range(len(b[0])):
            for k in range(len(b)):
                res[i][j] = min(a[i][k] + b[k][j], res[i][j])

    return res


for _ in [0] * T:
    N, K = list(map(int, input().split()))
    A = list(map(int, input().split()))

    V = create_array3(N, 2, 2, INF)

    for i in range(N):
        V[i][1][1] = A[i]
        V[i][1][0] = A[i]
        V[i][0][1] = 0

    e = [[INF, INF], [0, 0]]

    def op(a, b):
        if a == e:
            return b
        if b == e:
            return a

        return mat_mul(a, b)

    seg = SegTree(op, e, V)
    ans = INF

    for i in range(N - K + 1):
        ans = min(mat_mul(seg.prod(i, min(i + K, N)), [[0], [INF]])[1][0], ans)
        ans = min(mat_mul(seg.prod(i, min(i + K + 1, N)), [[0], [INF]])[1][0], ans)

    print(ans)
