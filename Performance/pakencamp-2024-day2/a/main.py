N = int(input())
A = list(map(int, input().split()))
A.sort(reverse=True)

print(A[3] - A[4])
