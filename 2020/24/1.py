import sys
l = sys.stdin.read().strip().split('\n')

dir = {
    'w': (-2, 0),
    'e': (2, 0),
    'nw': (-1, 1),
    'ne': (1, 1),
    'se': (1, -1),
    'sw': (-1, -1)
}
black = set()

for k in l:
    i = x = y = 0
    while i < len(k):
        s = k[i]
        i += 1
        if s != 'e' and s != 'w':
            s += k[i]
            i += 1
        x += dir[s][0]
        y += dir[s][1]
    if (x, y) in black:
        black.remove((x,y))
    else:
        black.add((x,y))

print(len(black))
