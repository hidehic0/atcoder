N, M = map(int, input().split())


def factorization(n: int):
    """
    nを素因数分解します
    計算量は、√Nです(要改善)
    複数回素因数分解を行なう場合は、√N以下の素数を列挙したので試し割りした法が速いです
    """
    result = []
    tmp = n
    for i in range(2, int(-(-(n**0.5) // 1)) + 1):
        if tmp % i == 0:
            cnt = 0
            while tmp % i == 0:
                cnt += 1
                tmp //= i
            result.append([i, cnt])

    if tmp != 1:
        result.append([tmp, 1])

    if result == []:
        result.append([n, 1])

    return result


res = factorization(N)
ans = 1
MOD = 998244353
res.append([3, 0])
res.sort()
M -= 1
for p, k in res:
    if p == 2:
        res[1][1] += k
    ans *= pow(p + 1, min(k, M), MOD)
    ans *= pow(p, k - min(k, M), MOD)
    ans %= MOD
    M -= min(k, M)

if res[0][0] == 2:
    inv = pow(pow(3, res[0][1]), MOD - 2, MOD)
    ans *= inv
    ans %= MOD

print(ans)
