import sys
i = sys.stdin.read().strip().split('\n')
x = y = 0
d = 0
l = ['E', 'N', 'W', 'S']
for t in i:
    a, b = t[0], int(t[1:])
    dir = {
        'N': (0, b),
        'S': (0, -b),
        'E': (b, 0),
        'W': (-b, 0)
    }
    if a == 'L':
        d = (d + b / 90) % 4
    elif a == 'R':
        d = (d - b / 90 + 4) % 4
    else:
        g = l[int(d)] if a == 'F' else a
        xt, yt = dir[g]
        x += xt
        y += yt
print(abs(x) + abs(y))
