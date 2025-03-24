import random

a = random.randrange(10, 15)
b = random.randrange(2, 4)

print(a, b)
print(*[random.randint(1, 2) for _ in [0] * a])
print(*[random.randint(1, 2) for _ in [0] * b])
