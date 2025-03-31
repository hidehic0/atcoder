N, Q = map(int, input().split())
A = list(map(int, input().split()))

if Q != 1 or N > 2000:
    exit()

left, right = map(int, input().split())
left -= 1
right -= 1

L = list(range(left, right + 1))
