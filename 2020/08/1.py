import sys
i = sys.stdin.read().strip().split('\n')
acc = j = 0
s = set()
while j not in s:
    s.add(j)
    x, y = i[j].split(' ')
    y = int(y)
    if x == 'acc':
        acc += y
        j += 1
    elif x == 'jmp':
        j += y
    elif x == 'nop':
        j += 1
print(acc)
