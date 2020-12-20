import sys
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

def printM(m):
    for x in m:
        for y in x:
            print(y, end='')
        print()
    print()

l = sys.stdin.read().strip().split('\n')
l = [list(i) for i in l]
print(foundedMonster(l))
res = 0
for x in l:
    res += x.count('#')
print(res)
