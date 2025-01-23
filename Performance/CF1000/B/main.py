import heapq

T = int(input())

while T:
    N, L, R = map(int, input().split())
    A = list(map(int, input().split()))
    ans = 1 << 63

    for l in range(N):
        for r in range(l, N):
            A[l : r + 1] = reversed(A[l : r + 1])

            ans = min(sum(A[L - 1 : R]), ans)

    print(ans)
    T -= 1
