import sys
a = list(map(int, sys.stdin.read().strip().split('\n')))
for i in a:
    d = 2020 - i
    if d in a:
        print(i*d)
        break
