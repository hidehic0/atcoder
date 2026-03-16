L, R, D, U = map(int, input().split())

ans = 0

for i in range(L, R + 1):
    for k in range(D, U + 1):
        if max(abs(i), abs(k)) % 2 == 0:
            ans += 1

print(ans)
