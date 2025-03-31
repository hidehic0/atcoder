from collections import deque

N, K, sub_id = map(int, input().split())


ans = set()

for u in range(N):
    Q = list(range(1, K + 1))
    back_res = None

    for _ in [0] * K:
        print(f"? {u + 1}", end=" ")
        print(*Q)

        T = int(input())

        if back_res != T and (back_res is not None):
            oa, ob = u + 1, back_res
            a, b = min(oa, ob), max(oa, ob)
            ans.add((a, b, Q[-1]))

        Q.append(Q.pop(0))
        back_res = T

print("!")
print(len(ans))
for l in ans:
    print(*l)
