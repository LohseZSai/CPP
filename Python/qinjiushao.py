# coding=utf-8
import numpy as np
#输入集合元素个数（也可以说是矩阵的阶数）
n = int(input())
amat1,amat2 = np.array([[0]*n for k in range(n)]),np.array([[0]*n for k in range(n)])
# 在此输入关系R，即构成矩阵
R = [(1, 3), (1, 5), (2, 5), (4, 5), (5, 4), (6, 3), (3, 2)]
for i, j in R:
    amat1[i-1][j-1] = 1
#将amat2变为单位矩阵(不调包)
for i in range(n):
    amat2[i][i] = 1
j = 0
B = amat1
while(j <= n - 1):
        B = np.dot(amat1,amat2 + B)
        j += 1
##最后一步是对关系矩阵进行处理
re = np.where(B > 1,1,B)
print(re)


