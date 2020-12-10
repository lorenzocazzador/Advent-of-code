import sys
l = list(map(int,sys.stdin.read().strip().split('\n')))

def f(n):
    if n == len(l) - 1:
        return 1
    if n >= len(l):
        return 0
    if m[n] != -1:
        return m[n]
    j = n + 1
    ans = 0
    while j < len(l) and l[j] - l[n] <= 3:
        ans += f(j)
        j += 1
    m[n] = ans
    return ans

l.append(0)
l.append(max(l) + 3)
l.sort()
m = [-1 for i in range(len(l))]
print(f(0))
