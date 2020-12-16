import sys
l = sys.stdin.read().strip().split('\n\n')

def isValid(t):
    for x in r:
        if x[1] <= t and t <= x[2]:
            return True
    return False

def aggCand(i, val):
    candi = set()
    for x in r:
        if x[1] <= val and val <= x[2]:
            candi.add(x[0])
    cand[i] &= candi

r = []
fields = set()
for x in l[0].split('\n'):
    n = x[:x.find(': ')]
    fields.add(n)
    t = x[x.find(': ')+1:]
    r1, r2 = t.split(' or ')
    a, b = list(map(int,r1.split('-')))
    c, d = list(map(int,r2.split('-')))
    r.append((n,a,b))
    r.append((n,c,d))

l[2] = l[2].split('\n')[1:]
v = []
for x in l[2]:
    val = True
    for t in x.split(','):
        if not isValid(int(t)):
            val = False
    if val:
        v.append(list(map(int,x.split(','))))

cand = []
found = [''] * len(v[0])
for x in range(len(v[0])):
    cand.append(fields.copy())
for t in v:
    for i,f in enumerate(t):
        aggCand(i,f)

agg = True
while agg:
    agg = False
    for i, c in enumerate(cand):
        if len(c) == 1 and found[i] == '':
            fi = list(c)[0]
            found[i] = fi
            for se in cand:
                if len(se) != 1 and fi in se:
                    se.remove(fi)
                    agg = True

l[1] = l[1].split('\n')[1]
res = 1
for i, x in enumerate(l[1].split(',')):
    if found[i].startswith('departure'):
        res *= int(x)
print(res)
