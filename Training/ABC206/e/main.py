l = list(map(int, input().split()))
L, R = l[0], l[1]

cnt = [0] * (R + 1)

ans = 0

for g in reversed(range(2, R + 1)):
    cnt[g] = ((R // g) - ((L - 1) // g)) ** 2

    ng = g * 2

    while ng <= R:
        cnt[g] -= cnt[ng]
        ng += g

for g in range(2, R + 1):
    ans += cnt[g]

    if L <= g <= R:
        ans -= ((R // g) - ((L - 1) // g)) * 2
        ans += 1

print(ans)
