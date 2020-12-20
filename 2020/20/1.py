import sys, math
l = sys.stdin.read().strip().split('\n\n')
t = []
for x in l:
    x = x.split('\n')
    a = int(x[0][x[0].find(' ')+1:x[0].find(':')])
    b = x[1:]
    t.append((a,b))

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

res = 1
for x in t:
    k = [x[1][i][0] for i in range(len(x[1]))]
    z = [x[1][i][-1] for i in range(len(x[1]))]

    a, b = check(list(x[1][0]), x[0]), check(list(x[1][-1]), x[0])
    c, d = check(k, x[0]), check(z, x[0])

    if (a ^ b) and (c ^ d):
        print(x[0])
        res *= x[0]
print(res)
