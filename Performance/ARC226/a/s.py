N = int(input())
L = [list(map(int, input().split())) for _ in [0] * N]
L.sort()

ans = 0

for bit in range(1 << N):
    flag = True
    for i in range(N):
        for k in range(N):
            if (bit >> i) & 1 != (bit >> k) & 1:
                continue

            if not (L[i][1] <= L[k][0] or L[k][1] <= L[i][0]):
                flag = False
                break

    ans += int(flag)

print(ans)
