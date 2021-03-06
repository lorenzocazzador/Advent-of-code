def getSeatID(s):
    r = s[:7].replace('F','0').replace('B','1')
    c = s[-3:].replace('L','0').replace('R','1')
    return int(r, 2) * 8 + int(c, 2)

import sys
ans = 0
for l in sys.stdin.read().strip().split('\n'):
    ans = max(ans, getSeatID(l))
print(ans)
