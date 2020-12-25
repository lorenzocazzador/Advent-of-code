import sys
c, d = map(int, sys.stdin.read().strip().split('\n'))
BASE = 7
MOD = 20201227
x = 0
while pow(BASE, x, MOD) != c:
    x += 1
print(pow(d, x, MOD))
