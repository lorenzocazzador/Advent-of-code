import sys, math
l = sys.stdin.read().strip().split('\n\n')
t = []
for x in l:
    x = x.split('\n')
    a = int(x[0][x[0].find(' ')+1:x[0].find(':')])
    b = x[1:]
    t.append((a,b))

def printM(m):
    for x in m:
        for y in x:
            print(y, end='')
        print()
    print()

def check(k, ind):
    for x in t:
        if x[0] == ind:
            continue

        a = [x[1][i][0] for i in range(len(x[1]))]
        b = [x[1][i][-1] for i in range(len(x[1]))]
        c, d = list(x[1][0]), list(x[1][-1])

        if k == a or k == a[::-1] or k == b or k == b[::-1] or k == c or k == c[::-1] or k == d or k == d[::-1]:
            return True
    return False

def getReversedRow(m):
    new = []
    for x in m:
        new.append(x[::-1])
    return new

def getRotatedSx90(m):
    new = [[] for i in range(len(m))]
    for x in m:
        for i,y in enumerate(x):
            new[-i-1].append(y)
    return new

def getRotatedDx90(m):
    new = [[] for i in range(len(m))]
    for x in reversed(m):
        for i,y in enumerate(x):
            new[i].append(y)
    return new


def getNeighbour(k, ind, left):
    for id, m in t:
        if id == ind:
            continue

        le = [m[i][0] for i in range(len(m))]
        ri = [m[i][-1] for i in range(len(m))]
        up, do = list(m[0]), list(m[-1])

        if k == le:
            # left: original, up: reverse col and rot dx 90
            return (id, m if left else getRotatedDx90(m[::-1]))
        elif k == le[::-1]:
            # left: reverse col, up: rot dx 90
            return (id, m[::-1] if left else getRotatedDx90(m))
        elif k == ri:
            # left: reverse row, up: rot sx 90
            return (id, getReversedRow(m) if left else getRotatedSx90(m))
        elif k == ri[::-1]:
            # left: reverse col and row, up: reverse col and rot sx 90
            return (id, getReversedRow(m[::-1]) if left else getRotatedSx90(m[::-1]))
        elif k == up:
            # left: reverse row and rotate sx 90, up: original
            return (id, getRotatedSx90(getReversedRow(m)) if left else m)
        elif k == up[::-1]:
            # left: rotate sx 90, up: reverse row
            return (id, getRotatedSx90(m) if left else getReversedRow(m))
        elif k == do:
            # left: rotate dx 90, up: reverse col
            return (id, getRotatedDx90(m) if left else m[::-1])
        elif k == do[::-1]:
            # left: reverse row and rotate dx 90, up: reverse row and reverse col
            return (id, getRotatedDx90(getReversedRow(m)) if left else getReversedRow(m)[::-1])
    return 'ERROR'

side = int(math.sqrt(len(t)))
im = [[(-1, []) for i in range(side)] for i in range(side)]
ul = (-1, [])
for x in t:
    k = [x[1][i][0] for i in range(len(x[1]))]
    z = [x[1][i][-1] for i in range(len(x[1]))]

    a, b = check(list(x[1][0]), x[0]), check(list(x[1][-1]), x[0])
    c, d = check(k, x[0]), check(z, x[0])

    if (a ^ b) and (c ^ d):
        if not a and not c:
            ul = x
        elif not a and not d:
            ul = (x[0], getRotatedSx90(x[1]))
        elif not b and not c:
            ul = (x[0], getRotatedDx90(x[1]))
        elif not b and not d:
            ul = (x[0], getRotatedDx90(getRotatedDx90(x[1])))
        break

im[0][0] = ul
for k in range(0, side):
    for i in range(1, side):
        prec = [im[k][i-1][1][j][-1] for j in range(len(im[k][i-1][1]))]
        im[k][i] = getNeighbour(prec, im[k][i-1][0], True)
    if k+1 < side:
        im[k+1][0] = getNeighbour(list(im[k][0][1][-1]), im[k][0][0], False)

# remove borders
for a in range(side):
    for b in range(side):
        id, m = im[a][b]
        for x in range(len(m)):
            m[x] = m[x][1:len(m[x])-1]
        im[a][b] = (im[a][b][0], im[a][b][1][1:len(m)-1])

side_tile = len(im[0][0][1])
new_side = side_tile * side
im_def = [['' for i in range(new_side)] for i in range(new_side)]
for a in range(new_side):
    for b in range(new_side):
        im_def[a][b] = im[a//side_tile][b//side_tile][1][a%side_tile][b%side_tile]

monster = ['                  # ',
           '#    ##    ##    ###',
           ' #  #  #  #  #  #   ']
pos = []
for i,x in enumerate(monster):
    for j,y in enumerate(x):
        if y == '#':
            pos.append((i,j))

def foundedMonster(m):
    globFound = False
    for a in range(len(m)):
        for b in range(len(m[a])):
            found = True
            for x,y in pos:
                if a+x >= len(m) or b+y >= len(m[a+x]) or m[a+x][b+y] != '#':
                    found = False
                    break
            if found:
                for x,y in pos:
                    m[a+x][b+y] = 'O'
                globFound = True
    return globFound

print(foundedMonster(im_def))
res = 0
for x in im_def:
    res += x.count('#')
print(res)
