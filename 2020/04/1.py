import sys
l = sys.stdin.read().split('\n\n')
res = 0
for p in l:
    x = p.split()
    c = 0
    for i in x:
        s = i.split(':')[0]
        c += (s != 'cid')
    res += (c == 7)
print(res)
