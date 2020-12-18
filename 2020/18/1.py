import sys
l = sys.stdin.read().strip().replace(' ','').split('\n')

def getUpdatedRes(res, num, op):
    if num != '':
        if op == '*':
            res *= int(num)
        else:
            res += int(num)
    return res

def f(ex):
    i = res = 0
    op, num = '', ''
    while i < len(ex):
        if ex[i] == '(':
            tmp_res = f(ex[i+1:])
            res = getUpdatedRes(res, tmp_res[0], op)
            i += tmp_res[1]
        elif ex[i] == ')':
            res = getUpdatedRes(res, num, op)
            return (res, i+2)
        elif ex[i].isdigit():
            num += ex[i]
            i += 1
        else:
            res = getUpdatedRes(res, num, op)
            num = ''
            op = ex[i]
            i += 1
    res = getUpdatedRes(res, num, op)
    return res

res = 0
for e in l:
    res += f(e)
print(res)
