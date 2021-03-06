import sys
r, m = sys.stdin.read().strip().split('\n\n')

def f(r):
    if rul[r][0] == 0:
        return [rul[r][1]]

    if r in memo:
        return memo[r]

    res = []
    # for every rules
    for x in rul[r][1]:
        t = ['']
        # iterate subrules
        for j in x:
            h = f(j)
            tmp = []
            for a in t:
                for b in h:
                    tmp.append(a+b)
            t = tmp
        res.extend(t)
    memo[r] = res
    return res


rul = {}
for x in r.split('\n'):
    n, l = x.split(': ')
    n = int(n)
    if '"' in l:
        rul[n] = (0, l[1])
    else:
        k = []
        for j in l.split(' | '):
            k.append(list(map(int,j.split(' '))))
        rul[n] = (1, k)

memo = {}
p = f(0)
res = sum([i in p for i in m.split('\n')])
print(res)
