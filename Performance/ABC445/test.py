def eratosthenes(n: int) -> list[int]:
    """エラトステネスの篩

    n以下の素数を列挙します
    計算量は、O(n log log n)です
    先程の素数判定法で列挙するよりも、少し速いです
    列挙した素数は昇順に並んでいます
    """
    primes = [True] * (n + 1)
    primes[0], primes[1] = False, False
    i = 2
    while i**2 <= n:
        if primes[i]:
            for k in range(i * 2, n + 1, i):
                primes[k] = False

        i += 1

    return [i for i, p in enumerate(primes) if p]


def factorization_plural(L: list[int]) -> list[list[tuple[int, int]]]:
    """複数の数の素因数分解

    計算量は、O(N * (√max(L) log log √max(L)))
    みたいな感じです

    最初に素数を列挙するため、普通の素因数分解より効率がいいです
    """
    primes = eratosthenes(int(max(L) ** 0.5) + 20)

    def solve(n):
        t = []
        for p in primes:
            if n % p == 0:
                cnt = 0
                while n % p == 0:
                    cnt += 1
                    n //= p

                t.append((p, cnt))

        if n != 1:
            t.append((n, 1))

        if t == []:
            t.append((n, 1))

        return t

    return [solve(n) for n in L]


T = int(input())
M = 998244353 - 2

for _ in [0] * T:
    N = int(input())
    L = factorization_plural(list(map(int, input().split())))
    D: dict[int, list] = {}

    for l in L:
        for k, v in l:
            if k not in D:
                D[k] = [v]
            else:
                D[k].append(v)

    ans = 1

    for k in D.keys():
        D[k].sort()
        ans *= pow(k, D[k][-1], 998244353)
        ans %= 998244353

    res = []

    for i in range(N):
        cur = ans

        for k, v in L[i]:
            if k == 1:
                continue

            if len(D[k]) == 1:
                cur *= pow(pow(k, v, 998244353), M, 998244353)
                cur %= 998244353
            elif D[k][-1] == v and D[k][-1] != D[k][-2]:
                cur *= (
                    pow(pow(k, v, 998244353), M, 998244353)
                    * pow(k, D[k][-2], 998244353)
                ) % 998244353
                cur %= 998244353

        print(cur, end=" ")

    print()
