import sys
l = sys.stdin.read().strip().split('\n')

def getNumber(v, mask):
    ans = ''
    v = bin(v)[2:].zfill(len(mask))
    for i in range(len(mask)):
        ans += v[i] if mask[i] == 'X' else mask[i]
    return int(ans, 2)

mask = ''
mem = dict()
for x in l:
    if x[:4] == 'mask':
        mask = x[7:]
    else:
        ad = int(x.replace('[',']').split(']')[1])
        v = int(x[x.find('=')+2:])
        num = getNumber(v, mask)
        mem[ad] = num
print(sum(mem.values()))
