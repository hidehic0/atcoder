N = int(input())
A = list(map(int, input().split()))

for K in reversed(range(N // 2 + 1)):
    a = A[:K]
    b = A[N - K :]

    for t in range(K):
        if a[t] <= b[t] // 2:
            continue
        else:
            break
    else:
        print(K)
        exit()
