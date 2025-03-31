N = int(input())
P = list(map(lambda x: x - 1, input().split()))
L = [0] * N

for p in P:
    L[p] += 1

if L.count(0) > 5:
    exit()
