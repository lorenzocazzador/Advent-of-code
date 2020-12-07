import sys
d = {}

def solve(x):
    if x not in d:
        return set()
    ans = set(d[x])
    for t in d[x]:
        ans_tmp = solve(t)
        for f in ans_tmp:
            ans.add(f)
    return ans

for l in sys.stdin.read().strip().split('\n'):
    f, s = l.split(' bags contain ')
    s = s.replace('.', ', ').replace('bags', 'bag').split(' bag, ')
    for x in s:
        if x == '' or x == 'no other':
            continue
        c = x[x.find(' ')+1:]
        d.setdefault(c,[]).append(f)

print(len(solve('shiny gold')))
