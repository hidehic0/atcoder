from itertools import combinations


class UnionFind:
    def __init__(self, n):
        self.n = n
        self.data = [-1] * self.n

    def root(self, x):
        if self.data[x] < 0:
            return x
        else:
            res = self.root(self.data[x])
            return res

    def merge(self, a, b):
        a = self.root(a)
        b = self.root(b)

        if a == b:
            return

        if self.data[a] > self.data[b]:
            a, b = b, a

        self.data[a] += self.data[b]
        self.data[b] = a

    def size(self, x):
        return -self.data[self.root(x)]

    def same(self, a, b):
        return UF.root(a) == UF.root(b)


N, M, K = map(int, input().split())
R = list(map(int, input().split()))

if R.count(1) == N:
    UF = UnionFind(N)

    for _ in [0] * M:
        u, v = map(int, input().split())
        u -= 1
        v -= 1
        UF.merge(u, v)

    S = set()
    L = []

    for i in range(N):
        rt = UF.root(i)
        if rt not in S:
            S.add(rt)
            L.append(UF.size(i))

    L.sort(reverse=True)
    su = sum(L[:K])

    for _ in [0] * su:
        print(1)

    for _ in [0] * (N - su):
        print(-1)
elif M == 0:
    R.sort(reverse=True)

    for i in range(N):
        if i >= K:
            print(-1)
        else:
            print(R[i])
elif N <= 10:
    G = [[] for _ in [0] * N]
    for _ in [0] * M:
        u, v = map(int, input().split())
        u -= 1
        v -= 1
        G[u].append(v)
        G[v].append(u)

    for i in range(N):
        ng, ok = -1, 1 << 61

        while ok - ng > 1:
            mid = (ok + ng) // 2

            for c in combinations(range(N), K):
                ST = list(c)
                FLAG = set(c)

                while ST:
                    cur = ST.pop()
                    if R[cur] < mid:
                        FLAG.discard(cur)
                        continue

                    for nxt in G[cur]:
                        if R[nxt] >= mid and nxt not in FLAG:
                            FLAG.add(nxt)
                            ST.append(nxt)

                if len(FLAG) >= i + 1:
                    break
            else:
                ok = mid
                continue

            ng = mid

        print(ng)
