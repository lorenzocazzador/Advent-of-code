import sys
l = sys.stdin.read().strip().split('\n')
all = {}
ing = []
for x in l:
    i, a = x.split(' (contains ')
    i = set(i.split(' '))
    a = a[:-1].split(', ')

    ing.extend(i)

    for k in a:
        if k in all:
            all[k] &= i
        else:
            all[k] = i.copy()

for x in all.keys():
    for k in all[x]:
        ing = [v for v in ing if v != k]
print(len(ing))
