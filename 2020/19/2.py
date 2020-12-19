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

def isValid(s):
    # 0: 8 11
    # 8: 42 | 42 8
    # 11: 42 31 | 42 11 31
    a, b = f(42), f(31)
    firstHalf = True
    counta = countb = 0
    for i in range(0, len(s), len(a[0])):
        sub = s[i:i+len(a[0])]
        if firstHalf:
            if sub in a:
                counta += 1
            elif sub in b:
                countb += 1
                firstHalf = False
            else:
                return False
        else:
            if sub not in b:
                return False
            countb += 1
    return counta > countb and counta > 1 and countb > 0

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
res = sum([isValid(i) for i in m.split('\n')])
print(res)
