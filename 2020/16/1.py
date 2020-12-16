import sys
l = sys.stdin.read().strip().split('\n\n')

def isValid(t):
    for x in r:
        if x[0] <= t and t <= x[1]:
            return True
    return False

r = []
for x in l[0].split('\n'):
    t = x[x.find(': ')+1:]
    r1, r2 = t.split(' or ')
    a, b = list(map(int,r1.split('-')))
    c, d = list(map(int,r2.split('-')))
    r.append((a,b))
    r.append((c,d))

res = 0
l[2] = l[2].split('\n')[1:]
for x in l[2]:
    for t in x.split(','):
        if not isValid(int(t)):
            res += int(t)
print(res)
