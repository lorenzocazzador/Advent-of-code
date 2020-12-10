import sys
l = list(map(int,sys.stdin.read().strip().split('\n')))
p = c1 = 0
c3 = 1
l.sort()
for x in l:
    d = x - p
    c1 += (d == 1)
    c3 += (d == 3)
    p = x
print(c1 * c3)
