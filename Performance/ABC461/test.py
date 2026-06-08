from itertools import accumulate


H, W, K = list(map(int, input().split()))
L = [[0] * W for _ in [0] * H]

for i in range(H):
    T = input()

    for k in range(W):
        if T[k] == "1":
            L[i][k] += 1

    L[i] = list(accumulate(L[i], initial=0))

ans = 0

C = [0] * (H * W * 3)

for a in range(W):
    for b in range(a, W):
        A = list(accumulate([L[i][b + 1] - L[i][a] for i in range(H)], initial=0))

        for i in range(1, H + 1)[::-1]:
            ans += C[A[i] + K]

            C[A[i]] += 1

        ans += C[K]

        for i in range(1, H + 1)[::-1]:
            C[A[i]] -= 1


print(ans)
