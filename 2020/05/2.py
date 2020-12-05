def getSeatID(s):
    r = s[:7].replace('F','0').replace('B','1')
    c = s[-3:].replace('L','0').replace('R','1')
    return int(r, 2) * 8 + int(c, 2)

import sys
ids = []
for l in sys.stdin.read().strip().split('\n'):
    ids.append(getSeatID(l))
ids.sort()
for i in range(len(ids)):
    x = ids[0] + i
    if x not in ids and x - 1 in ids and x + 1 in ids:
        print(x)
