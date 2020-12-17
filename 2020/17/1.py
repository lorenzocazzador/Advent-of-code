import sys
l = sys.stdin.read().strip().split('\n')

def inside(i, j, k):
    return i >= 0 and i < size and j >= 0 and j < size and k >= 0 and k < size

def activeNear(i, j, k):
    ans = 0
    for a in {-1, 0, 1}:
        for b in {-1, 0, 1}:
            for c in {-1, 0, 1}:
                if a == 0 and b == 0 and c == 0:
                    continue
                ni, nj, nk = i+a, j+b, k+c
                if inside(ni, nj, nk):
                    ans += m[ni][nj][nk]
    return ans

cycles = 6
size = len(l) + cycles * 2

m = [[[0 for i in range(size)] for i in range(size)] for i in range(size)]
mid = int(size / 2)
st = mid - int(len(l) / 2)
for i,x in enumerate(l):
    for j,y in enumerate(x):
        m[mid][st+i][st+j] = 1 if y == '#' else 0

for c in range(cycles):
    t = [[[0 for i in range(size)] for i in range(size)] for i in range(size)]
    for i in range(len(m)):
        for j in range(len(m[i])):
            for k in range(len(m[i][j])):
                act = activeNear(i, j, k)
                if m[i][j][k] == 1:
                    t[i][j][k] = 1 if act == 2 or act == 3 else 0
                else:
                    t[i][j][k] = 1 if act == 3 else 0
    m = t

res = 0
for i in range(len(m)):
    for j in range(len(m[i])):
        for k in range(len(m[i][j])):
            res += m[i][j][k]
print(res)
