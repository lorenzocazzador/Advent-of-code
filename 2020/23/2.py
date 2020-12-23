import sys
l = list(map(int,list(sys.stdin.read().strip())))
moves = int(1e7)
maxv = int(1e6)
next = {}
for i in range(maxv):
    if i + 1 < len(l):
        next[l[i]] = l[i+1]
    elif i + 1 == len(l):
        next[l[i]] = i + 2
    else:
        next[i + 1] = i + 2
next[maxv] = l[0]

c = l[0]
for m in range(moves):
    c1 = next[c]
    c2 = next[c1]
    c3 = next[c2]

    next[c] = next[c3]

    dest = (c - 2 + maxv) % maxv + 1
    while dest in [c1, c2, c3]:
        dest = (dest - 2 + maxv) % maxv + 1

    next[dest], next[c3] = c1, next[dest]

    c = next[c]

print(next[1]*next[next[1]])
