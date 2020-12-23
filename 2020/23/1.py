import sys
l = list(map(int,list(sys.stdin.read().strip())))
moves = 100
c = 0

for m in range(moves):
    x = l*2
    v = l[c]
    sub = x[c+1:c+4]
    for k in sub:
        l.remove(k)
    d = (v - 2 + 9) % 9 + 1
    while d not in l:
        d = (d - 2 + 9) % 9 + 1
    pos = l.index(d)
    l = l[:pos+1] + sub + l[pos+1:]
    c = (l.index(v) + 1) % 9

one = l.index(1)
print(*(l[one+1:]+l[:one]), sep='')
