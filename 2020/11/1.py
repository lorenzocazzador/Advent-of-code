import sys
l = sys.stdin.read().strip().split('\n')

def countAdj(i, j):
    c = 0
    for x in {-1, 0, 1}:
        for y in {-1, 0, 1}:
            if x == 0 and y == 0:
                continue
            if i+x >= 0 and i+x < len(l) and j+y >= 0 and j+y < len(l[0]):
                c += l[i+x][j+y] == '#'
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
            elif l[i][j] == '#' and a >= 4:
                s += 'L'
                ans -= 1
                change = True
            else:
                s += l[i][j]
        c.append(s)
    l = c
print(ans)
