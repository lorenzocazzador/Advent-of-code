import sys
l = list(map(int,sys.stdin.read().strip().split('\n')))
l.append(0)
l.sort()
m = [0] * len(l)
m[0] = 1
for i in range(len(m)):
    j = i + 1
    while j < len(l) and l[i] + 3 >= l[j]:
        m[j] += m[i]
        j += 1
print(m[-1])
