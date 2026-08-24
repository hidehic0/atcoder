import random

N = 20
print(N)
S = [chr(97 + random.randint(0, 3)) for _ in [0] * N]

print("".join(S))
