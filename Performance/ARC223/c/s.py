T = int(input())

for _ in [0] * T:
    N = int(input())
    A = list(map(int, input().split()))

    ans = 1

    for i in range(N):
        for k in range(i + 1, N):
            ans *= abs(A[i] - A[k])
            ans %= N

    print(ans % N)
