import sys
l = list(map(int, sys.stdin.read().strip().split('\n')))
preamble_length = 25
d = []
for i in range(len(l)):
    if i >= preamble_length:
        p = 0
        for x in d:
            t = l[i] - x
            if t != l[i] and t in d:
                p = 1
        if p == 0:
            print(l[i])
            break
        d.remove(l[i-preamble_length])
    d.append(l[i])
