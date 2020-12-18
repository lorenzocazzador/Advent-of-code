import sys
l = sys.stdin.read().strip().replace(' ','').split('\n')

def f(ex):
    i = 0
    num = ''
    listEx = []
    while i < len(ex):
        if ex[i] == '(':
            tmp_res = f(ex[i+1:])
            listEx.append(str(tmp_res[0]))
            i += tmp_res[1]
        elif ex[i] == ')':
            break
        elif ex[i].isdigit():
            num += ex[i]
            i += 1
        else:
            if num != '': listEx.append(num)
            num = ''
            listEx.append(ex[i])
            i += 1
    if num != '': listEx.append(num)
    newListEx = []
    op = ''
    for x in listEx:
        if x.isdigit():
            if op == '+':
                tmp = newListEx[-1] + int(x)
                del newListEx[-1]
                newListEx.append(tmp)
            else:
                newListEx.append(int(x))
        else:
            op = x
    res = 1
    for x in newListEx:
        res *= x
    return (res, i+2)

res = 0
for e in l:
    res += f(e)[0]
print(res)
