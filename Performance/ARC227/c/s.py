from collections import defaultdict

N = int(input())
S = input()
D = defaultdict(list)

for i in range(N):
    D[S[i]].append(i)

if min([len(l) for l in D.values()]) == 1:
    print(1)
    exit()

dp = [False] * (1 << N)
dp[-1] = True

for bit in range(1 << N)[::-1]:
    for l in D.values():
        cur = (l[-1] + 1) % N
        nb = 0

        for k in range(len(l)):
            while cur != l[k]:
                if (bit >> cur) & 1:
                    nb |= 1 << l[k]

                cur += 1
                cur %= N
            else:
                if (bit >> cur) & 1:
                    nb |= 1 << l[k]

                cur += 1
                cur %= N

        dp[nb] |= dp[bit]

ans = 10**10

for bit in range(1 << N):
    if dp[bit]:
        ans = min(ans, bit.bit_count())

print(ans)
