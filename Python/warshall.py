# coding=utf-8

import numpy as np


def Warshall(A, n):
    for k in range(n):
        for i in range(n):
            for j in range(n):
                A[i][j] = A[i][j] or (A[i][k] and A[k][j])

    return A


#在此输入矩阵的阶数
n = int(input())
amat1 = [[0]*n for k in range(n)]
# 在此输入关系R，即构成矩阵
R = [(1, 3), (1, 5), (2, 5), (4, 5), (5, 4), (6, 3), (3, 2)]
for i, j in R:
    amat1[i-1][j-1] = 1
print(np.array(amat1))
print(np.array(Warshall(amat1, n)))
