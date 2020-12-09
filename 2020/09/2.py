import sys

def f(preamble_length):
    d = []
    for i in range(len(l)):
        if i >= preamble_length:
            p = False
            for x in d:
                t = l[i] - x
                p |= (t != l[i] and t in d)
            if not p:
                return l[i]
            d.remove(l[i-preamble_length])
        d.append(l[i])

l = list(map(int, sys.stdin.read().strip().split('\n')))
preamble_length = 25
r1 = f(preamble_length)

for length in range(2, len(l)):
    h = []
    s = 0
    for i in range(len(l) - length + 1):
        if i >= length:
            if s == r1:
                print(min(h) + max(h))
            s -= h[0]
            h.remove(h[0])
        h.append(l[i])
        s += l[i]
