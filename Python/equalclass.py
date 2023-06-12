# coding=gbk
#首先插入warshall的子程序用于求传递闭包
import numpy as np
#warshall法求传递闭包的代码
def Warshall(A, n):
    for k in range(n):
        for i in range(n):
            for j in range(n):
                A[i][j] = A[i][j] or (A[i][k] and A[k][j])

    return A
#第一步，输入矩阵
#若关系等价，即满足自反性、对称性、传递性
def Equals(B,m):
    #第一步判断自反性，若满足自反性的话，关系矩阵对角线上元素之和应该为阶数
    if np.trace(B) == m:
       for i in range(B.shape[0]):
        for j in range(B.shape[1]):
            if B[i][j] == B[j][i]:
                if Warshall(B,m).all() == B.all():
                    return "该关系是等价关系"
                else:
                    return "该关系不是等价关系"
            else:
                return "该关系不是等价关系"

    else:
        return "该关系不是等价关系"

#该函数用于输出等价类
def output(A,x):
    B = set()
    a = []
    while len(B) != 6:
        for i in A:
            count = 0
            C = set()
            for j in i:
                count += 1
                if j == 1:
                    C.add(count)
                    
            a.append(C)
        b = [str(i) for i in a]
        return set(b)
        
       
                    
                        
        
         #集合中元素，每一次都生成一个等价类集合
        
    


#输入矩阵的阶数，关系等信息
n = int(input())
x = {1,2,3,4,5,6}
amat = [[0]*n for k in range(n)]
R = [(1,1),(2,2),(3,3),(4,4),(5,5),(6,6),(1,4),(2,3),(2,6),(3,2),(3,6),(4,1),(6,2),(6,3)]
for i,j in R:
    amat[i-1][j-1] = 1
amat = np.array(amat)
print(Equals(amat,n))
print(amat)
print(f"等价类输出为：{output(amat,x)}")
#if Equals(amat,n) == '该关系是等价关系':
    




