import sys
a = list(map(int, sys.stdin.read().strip().split('\n')))
ans = -1
for i in a:
    for j in a:
        d = 2020 - i - j
        if d in a:
            ans = i*j*d
print(ans)
