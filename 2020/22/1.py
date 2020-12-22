import sys
from collections import deque

a, b = sys.stdin.read().strip().split('\n\n')
a = deque(map(int, a.split('\n')[1:]))
b = deque(map(int, b.split('\n')[1:]))

while a and b:
    c, d = a.popleft(), b.popleft()
    if c > d:
        a.extend([c, d])
    else:
        b.extend([d, c])

def getRes(x):
    x.reverse()
    return sum([(i+1) * v for i, v in enumerate(x)])

print(getRes(a if a else b))
