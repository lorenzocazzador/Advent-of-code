def byr(b):
    return int(b) >= 1920 and int(b) <= 2002

def iyr(b):
    return int(b) >= 2010 and int(b) <= 2020

def eyr(b):
    return int(b) >= 2020 and int(b) <= 2030

def hgt(b):
    e = b[-2:]
    r = b[:-2]
    if e == 'cm':
        return int(r) >= 150 and int(r) <= 193
    elif e == 'in':
        return int(r) >= 59 and int(r) <= 76
    else:
        return 0

def hcl(b):
    v = (b[0] == '#' and len(b[1:]) == 6)
    for i in b[1:]:
        v &= (i.isalpha() or i.isdigit())
    return v

def ecl(b):
    val = ['amb', 'blu', 'brn', 'gry', 'grn', 'hzl', 'oth']
    return b in val

def pid(b):
    return b.isdigit() and len(b) == 9

def cid(b):
    return 0

import sys
l = sys.stdin.read().split('\n\n')
res = 0
for p in l:
    x = p.split()
    c = 0
    for i in x:
        a = i.split(':')[0]
        b = i.split(':')[1]
        op = {
            'byr' : byr,
            'iyr' : iyr,
            'eyr' : eyr,
            'hgt' : hgt,
            'hcl' : hcl,
            'ecl' : ecl,
            'pid' : pid,
            'cid' : cid,
        }
        c += op[a](b)
    res += (c == 7)
print(res)
