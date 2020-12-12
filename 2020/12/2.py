import sys
i = sys.stdin.read().strip().split('\n')

def rotate(x, y, t):
    # rotate t times 90 degrees in clock-wise
    rot = {
        0: (x, y),
        1: (y, -x),
        2: (-x, -y),
        3: (-y, x)
    }
    return rot[t % 4]

x, y = 10, 1
xs = ys = 0
for t in i:
    a, b = t[0], int(t[1:])
    dir = {
        'N': (0, b),
        'S': (0, -b),
        'E': (b, 0),
        'W': (-b, 0)
    }
    if a == 'L':
        x, y = rotate(x, y, 4 - b / 90)
    elif a == 'R':
        x, y = rotate(x, y, b / 90)
    elif a == 'F':
        xs += x * b
        ys += y * b
    else:
        xt, yt = dir[a]
        x += xt
        y += yt
print(abs(xs) + abs(ys))
