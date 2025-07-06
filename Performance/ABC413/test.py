import random

n = 200
r = random.randrange(-4, 4)
a = random.randrange(-1000, 1000)

print(1)
print(n)
A = []

for i in range(n):
    A.append(a)
    a *= r

random.shuffle(A)

a = random.randrange(-1000, 1000)

while a == 0 or a in A:
    a = random.randrange(-1000, 1000)

A.append(a)

print(*A)
