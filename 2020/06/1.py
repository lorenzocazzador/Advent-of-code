import sys
ans = 0
for g in sys.stdin.read().strip().split('\n\n'):
    s = set()
    for a in g.split('\n'):
        for i in a:
            s.add(i)
    ans += len(s)
print(ans)
