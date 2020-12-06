import sys
ans = 0
for g in sys.stdin.read().strip().split('\n\n'):
    l = len(g.split('\n'))
    for i in range(26):
        ans += (g.count(chr(ord('a')+i)) == l)
print(ans)
