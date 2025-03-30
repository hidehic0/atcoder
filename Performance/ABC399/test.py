input()
N = int(input())
A = list(map(int, input().split()))

ans = 0

for i in range(2 * N - 1):
    for k in range(i + 2, 2 * N - 1):
        if A[i] != A[i + 1] and A[k] != A[k + 1]:
            ans += len(set([A[i], A[i + 1], A[k], A[k + 1]])) == 2

print(ans)
