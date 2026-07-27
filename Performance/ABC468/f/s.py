N = int(input())
P = list(map(int, input().split()))

ans = 0

for bit in range(1 << N):
    x, y, c = 0, 0, 0

    for i in range(N):
        if (bit >> i) & 1:
            if x < P[i]:
                x = P[i]
                c += 1
        else:
            if y < P[i]:
                y = P[i]
                c += 1

    ans = max(ans, c)

print(ans)
