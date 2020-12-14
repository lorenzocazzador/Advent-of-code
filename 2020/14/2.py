import sys
l = sys.stdin.read().strip().split('\n')

def getAddresses(ad, mask):
    ans = ''
    ad = bin(ad)[2:].zfill(len(mask))
    for i in range(len(mask)):
        ans += ad[i] if mask[i] == '0' else mask[i]
    f = ans.count('X')
    ret = []
    for i in range(2**f):
        b = bin(i)[2:].zfill(f)
        newA = ''
        j = 0
        for x in range(len(ans)):
            if ans[x] != 'X':
                newA += ans[x]
            else:
                newA += b[j]
                j += 1
        ret.append(newA)
    return ret

mask = ''
mem = dict()
for x in l:
    if x[:4] == 'mask':
        mask = x[7:]
    else:
        ad = int(x.replace('[',']').split(']')[1])
        v = int(x[x.find('=')+2:])
        ads = getAddresses(ad, mask)
        for t in ads:
            mem[int(t,2)] = v
print(sum(mem.values()))
