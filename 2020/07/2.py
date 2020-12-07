import sys
d = {}

def solve2(x):
    ans = 1
    for t in d[x]:
        ans += t[0] * solve2(t[1])
    return ans

for l in sys.stdin.read().strip().split('\n'):
    f, s = l.split(' bags contain ')
    s = s.replace('.', ', ').replace('bags', 'bag')
    s = s.split(' bag, ')
    d.setdefault(f,[])
    for x in s:
        if x == '' or x == 'no other':
            continue
        sp = x.find(' ')
        n = int(x[:sp])
        c = x[sp+1:]
        d[f].append([n,c])

print(solve2('shiny gold') - 1)
