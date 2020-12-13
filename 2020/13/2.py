import sys
a = int(input())
b = [(a, int(bus)) for a, bus in enumerate(input().split(',')) if bus != 'x']
#b.sort(key = lambda tup : tup[1], reverse = True)
res, inc = b[0]
for x in range(1, len(b)):
    a, mod = b[x]
    while (res + a) % mod != 0:
        res += inc
    inc *= mod
print(res)
