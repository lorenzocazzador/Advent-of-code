import sys
ans = 0
for l in sys.stdin.read().strip().split('\n'):
    x = l.split(' ')
    v = list(map(int,x[0].split('-')))
    c = x[1][0]
    w = x[2]
    ans += (w[v[0]-1] == c) ^ (w[v[1]-1] == c)
print(ans)
