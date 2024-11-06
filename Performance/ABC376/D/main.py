# ライブラリ
def pow(x: int, n: int, t: int = 1):
    if t == 1:
        ans = 1
        while n:
            if n % 2:
                ans = ans * x
            x = x * x
            n >>= 1
        return ans
    ans = 1
    while n:
        if n % 2:
            ans = (ans * x) % t
        x = (x * x) % t
        n >>= 1
    return ans


def is_prime(n: int) -> bool:
    if n == 1:
        return False

    i = 2
    s = n**0.5

    while i < s:
        if n % i == 0:
            return False

        i += 1

    return True


INF = 10**18
lowerlist = list("abcdefghijklmnopqrstuvwxyz")
upperlist = list("ABCDEFGHIJKLMNOPQRSTUVWXYZ")
# コード
from collections import deque

N, M = list(map(int, input().split()))
G = [[] for _ in [0] * N]

for _ in [0] * M:
    a, b = list(map(int, input().split()))

    G[a - 1].append(b - 1)

used = [INF] * N
used[0] = 0
q = deque([0])

while len(q) > 0:
    cur = q.popleft()

    for dst in G[cur]:
        if dst == 0:
            print(used[cur] + 1)
            exit()
        if used[dst] == INF:
            used[dst] = used[cur] + 1
            q.append(dst)

print(-1)
