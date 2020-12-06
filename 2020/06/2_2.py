import sys
ans = 0
for g in sys.stdin.read().strip().split('\n\n'):
    d = {}  # dictonary
    for a in g.split('\n'):
        for i in a:
            if (d.get(i) is None):
                d[i] = 1
            else:
                d[i] += 1
    sz = len(g.split('\n'))
    for i in range(26):
        l = chr(ord('a')+i)
        if d.get(l) is not None:
            ans += (d[l] == sz)
print(ans)
