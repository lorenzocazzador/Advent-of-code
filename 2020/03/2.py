def f(a, r, d):
    i, j, ans = 0, 0, 0
    while (i < len(a)):
        ans += (a[i][j%len(a[i])] == '#')
        i += d
        j += r
    return ans

import sys
a = sys.stdin.read().strip().split('\n')
print(f(a, 1, 1) * f(a, 3, 1) * f(a, 5, 1) * f(a, 7, 1) * f(a, 1, 2))
