# coding=utf-8
import numpy as np
#���뼯��Ԫ�ظ�����Ҳ����˵�Ǿ���Ľ�����
n = int(input())
amat1,amat2 = np.array([[0]*n for k in range(n)]),np.array([[0]*n for k in range(n)])
# �ڴ������ϵR�������ɾ���
R = [(1, 3), (1, 5), (2, 5), (4, 5), (5, 4), (6, 3), (3, 2)]
for i, j in R:
    amat1[i-1][j-1] = 1
#��amat2��Ϊ��λ����(������)
for i in range(n):
    amat2[i][i] = 1
j = 0
B = amat1
while(j <= n - 1):
        B = np.dot(amat1,amat2 + B)
        j += 1
##���һ���ǶԹ�ϵ������д���
re = np.where(B > 1,1,B)
print(re)


