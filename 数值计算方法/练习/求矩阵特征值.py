import numpy as np

print("请输入矩阵的行数：")
n = int(input())
print("请输入矩阵的每一行，输入完一行后点击回车")
mat = [list(map(float,input().split())) for i in range(n)]
mat = np.array(mat)
a, b = np.linalg.eig(mat)

print('打印特征值a：\n{}'.format(a))

print('打印特征向量b：\n{}'.format(b))