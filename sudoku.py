from __future__ import print_function
import pycosat
import sys
import re

try:
    input = raw_input
except NameError:
    pass

class block:
    def __init__(self, n):
        col = n%3
        row = n/3
        c = col*3
        r = row*3
        self.list = []
        self.num = 0
        for i in range(r, r+3):
            for j in range(c, c+3):
                self.list.append((i,j))
    def __iter__(self):
        return self
    
    def next(self):
        if self.num < 9:
            self.num += 1
            return self.list[self.num-1]
        else:
            raise StopIteration()

def conv(a, b, c):
    return a*81+b*9+c+1

def inverse(num):
    num -= 1
    a = num/81
    num %= 81
    b = num/9
    c = num % 9
    return (a,b,c)

def gen_cell_least():
    lst = []
    for i in range(0,9):
        for j in range(0,9):
            tmp = []
            for k in range(0,9):
                tmp.append(conv(i,j,k))
            lst.append(tmp)
    return lst

def gen_cell_most():
    lst = []
    for i in range(0,9):
        for j in range(0,9):
            for k in range(0,8):
                for l in range(k+1, 9):
                    lst.append([-conv(i,j,k), -conv(i,j,l)])
    return lst

def gen_row_least():
    lst = []
    for i in range(0,9):
        for k in range(0,9):
            tmp = []
            for j in range(0,9):
                tmp.append(conv(i,j,k))
            lst.append(tmp)
    return lst

def gen_row_most():
    lst = []
    for i in range(0,9):
        for k in range(0,9):
            for a in range(0,8):
                for b in range(a+1, 9):
                    lst.append([-conv(i,a,k), -conv(i,b,k)])
    return lst

def gen_col_least():
    lst = []
    for j in range(0,9):
        for k in range(0,9):
            tmp = []
            for i in range(0,9):
                tmp.append(conv(i,j,k))
            lst.append(tmp)
    return lst

def gen_col_most():
    lst = []
    for j in range(0,9):
        for k in range(0,9):
            for a in range(0,8):
                for b in range(a+1, 9):
                    lst.append([-conv(a,j,k), -conv(b,j,k)])
    return lst

def gen_block_least():
    lst = []
    for i in range(0,9):
        for j in range(0,9):
            tmp = []
            for k in block(i):
                tmp.append( conv(k[0], k[1], j) )
            lst.append(tmp)
    return lst

def gen_block_most():
    lst = []
    for i in range(0,9):
        for j in range(0,9):
            list1 = block(i).list
            for k in range(0,8):
                for l in range(k+1, 9):
                    lst.append([-conv(list1[k][0], list1[k][1], j),
                                                -conv(list1[l][0], list1[l][1], j)])
    return lst

def gen_facts():
    lst = []
    for i in range(0,9):
        s = input()
        for j in range(0,9):
            num = int(s[j])
            if num is not 0:
                lst.append([conv(i, j, num-1)])
    return lst

facts = gen_facts()
row = gen_row_least() + gen_row_most()
col = gen_col_least() + gen_col_most()
block = gen_block_least() + gen_block_most()
cell = gen_cell_least() + gen_cell_most()

rules = facts + row + col + block + cell
print(len(rules))
list = (pycosat.solve(rules))

matrix = []
for i in range(0,9):
    matrix.append([0]*9)

for k in list:
    if k>0:
        p,q,r = inverse(k)
        matrix[p][q] = r

for row in matrix:
    for ch in row:
        sys.stdout.write(str(ch+1))
    print()
