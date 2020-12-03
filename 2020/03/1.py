import sys
j, r = 0, 0
for l in sys.stdin.read().strip().split('\n'):
    r += (l[j%len(l)] == '#')
    j += 3
print(r)
