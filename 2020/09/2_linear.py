import sys
from collections import deque

def f(preamble_length):
    d = deque()
    for i in range(len(l)):
        if i >= preamble_length:
            p = False
            for x in d:
                t = l[i] - x
                p |= (t != l[i] and t in d)
            if not p:
                return int(l[i])
            d.popleft()
        d.append(l[i])
    return 0

l = list(map(int, sys.stdin.read().strip().split('\n')))
preamble_length = 25
r1 = f(preamble_length)

h = deque()
s = 0
for i in range(len(l)):
    s += l[i]
    h.append(l[i])
    while s > r1:
        s -= h[0]
        h.popleft()
    if s == r1:
        print(min(h) + max(h))
        break
