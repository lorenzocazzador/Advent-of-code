import sys
l = list(map(int, sys.stdin.read().strip().split(',')))
n = 30000000
map = [-1] * n
for i, x in enumerate(l):
    if i != len(l)-1:
        map[x] = i

prec = l[-1]
for i in range(len(l), n):
    tprec = 0
    if map[prec] != -1:
        tprec = i - 1 - map[prec]
    map[prec] = i - 1
    prec = tprec
print(prec)
