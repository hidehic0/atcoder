import random

a, b = random.randrange(12), random.randrange(12)

while a + b > 11:
    a, b = random.randrange(12), random.randrange(12)

c = random.randrange(12 - a - b)

print(1)
print(a, b, c)
