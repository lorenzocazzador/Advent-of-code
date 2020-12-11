import sys
l = sys.stdin.read().strip().split('\n')

def ins(i, j):
    return i >= 0 and i < len(l) and j >= 0 and j < len(l[0])

def iterate(i, j , di, dj):
    ans = 0
    while ins(i+di, j+dj) and l[i+di][j+dj] != 'L':
        i += di
        j += dj
        ans |= l[i][j] == '#'
    return ans

def countAdj(i, j):
    c = 0
    for dx in {-1, 0, 1}:
        for dy in {-1, 0, 1}:
            if not (dx == 0 and dy == 0):
                c += iterate(i, j, dx, dy)
    return c

change = True
ans = 0
while change:
    change = False
    c = []
    for i in range(len(l)):
        s = ''
        for j in range(len(l[i])):
            a = countAdj(i, j)
            if l[i][j] == 'L' and a == 0:
                s += '#'
                ans += 1
                change = True
            elif l[i][j] == '#' and a >= 5:
                s += 'L'
                ans -= 1
                change = True
            else:
                s += l[i][j]
        c.append(s)
    l = c
print(ans)
