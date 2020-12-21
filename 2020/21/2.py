import sys
l = sys.stdin.read().strip().split('\n')
all = {}
for x in l:
    i, a = x.split(' (contains ')
    i = set(i.split(' '))
    a = a[:-1].split(', ')

    for k in a:
        if k in all:
            all[k] &= i
        else:
            all[k] = i.copy()

cancelled = set()
updated = True
while updated:
    updated = False
    for x in all.keys():
        if len(all[x]) == 1:
            ing = list(all[x])[0]
            if ing not in cancelled:
                cancelled.add(ing)
                for y in all.keys():
                    if y != x:
                        all[y].discard(ing)
                        updated = True

res = [list(v)[0] for k,v in sorted(all.items())]
print(*res, sep=',')
