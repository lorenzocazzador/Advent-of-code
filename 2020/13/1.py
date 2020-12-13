import sys
a = int(input())
b = set(input().split(','))
b.remove('x')
b = list(map(int, b))
found = False
pa = a
while not found:
    for x in b:
        if a % x == 0:
            print((a - pa) * x)
            found = True
    a += 1
