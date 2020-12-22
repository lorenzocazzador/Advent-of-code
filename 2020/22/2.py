import sys
from collections import deque

a, b = sys.stdin.read().strip().split('\n\n')
a = deque(map(int, a.split('\n')[1:]))
b = deque(map(int, b.split('\n')[1:]))

def play(a, b):
    vis = set()
    while a and b:
        x = (tuple(a), tuple(b))
        if x in vis:
            return True
        vis.add(x)
        c, d = a.popleft(), b.popleft()
        if c <= len(a) and d <= len(b):
            na = deque(list(a)[:c])
            nb = deque(list(b)[:d])
            if play(na, nb):
                a.extend([c, d])
            else:
                b.extend([d, c])
        elif c > d:
            a.extend([c, d])
        else:
            b.extend([d, c])
    return a

def getRes(x):
    x.reverse()
    return sum([(i+1) * v for i, v in enumerate(x)])

play(a, b)
print(getRes(a if a else b))
