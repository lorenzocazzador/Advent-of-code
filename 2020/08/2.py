import sys

def f(i):
    acc = j = 0
    s = set()

    while j not in s and j < len(i):
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

    return -1 if j < len(i) else acc

i = sys.stdin.read().strip().split('\n')
ans = 0
for t in range(len(i)):
    x, y = i[t].split(' ')
    if x == 'jmp':
        i[t] = 'nop ' + y
        ans = max(ans, f(i))
        i[t] = 'jmp ' + y
    elif x == 'nop':
        i[t] = 'jmp ' + y
        ans = max(ans, f(i))
        i[t] = 'nop ' + y
print(ans)
