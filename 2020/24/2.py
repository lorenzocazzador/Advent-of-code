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

days = 100
for d in range(days):
    white = {}
    newB = set()
    for b in black:
        black_adj = 0
        for k, v in dir.items():
            adj = (b[0]+v[0], b[1]+v[1])
            if adj in black:
                black_adj += 1
            else:
                if adj in white:
                    white[adj] += 1
                else:
                    white[adj] = 1
        if black_adj == 1 or black_adj == 2:
            newB.add(b)
    for k, v in white.items():
        if v == 2:
            newB.add(k)
    black = newB

print(len(black))
