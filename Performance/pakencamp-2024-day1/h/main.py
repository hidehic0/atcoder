import sys

sys.set_int_max_str_digits(10**8)
sys.setrecursionlimit(10**9)


import pypyjit

pypyjit.set_param("max_unroll_recursion=-1")

N = int(input())
dp = [[(1, 1), (1, 0)]]
MOD = 998244353

if N > 3:
    b = N * pow(2, N - 3, MOD) % MOD
    a = b + pow(2, N - 2, MOD) % MOD
    print((a + b) % MOD)
    exit()

for i in range(1, N):
    new_dp = []
    new_dp.append(
        (dp[-1][0][0] + dp[-1][1][0], dp[-1][0][1] + dp[-1][1][0] + dp[-1][1][1])
    )
    new_dp.append((dp[-1][0][0] + dp[-1][1][0], dp[-1][0][1] + dp[-1][1][1]))
    new_dp[0] = (new_dp[0][0] % MOD, new_dp[0][1] % MOD)
    new_dp[1] = (new_dp[1][0] % MOD, new_dp[1][1] % MOD)
    dp.append(new_dp)

print((dp[N - 1][0][1] + dp[N - 1][1][1]) % MOD)
