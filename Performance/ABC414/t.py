N = int(input())
mod = 998244353

ans = pow(N, 2, mod)
inv = pow(2, -1, mod)
ans -= (((N * (N - 1)) % mod) * inv) % mod

for i in range(1, N + 1):
    ans -= N // i
    ans %= mod

print(ans)
