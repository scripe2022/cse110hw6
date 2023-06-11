#!/usr/bin/python3
import random

L = 200
R = 1000
n = random.randint(L, R)
print(n)
m = 10
for i in range(n):
    print(random.randint(1, m), end=' ')
print()