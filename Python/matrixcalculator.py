#下面主要运用numpy完成一个基本的矩阵计算器
import numpy as np
print("--------------请输入待操作矩阵的阶数和具体数值----------------")
n= int(input())
amat1 = np.array([ list(map(int,input().split())) for i in range(n) ])
#amat2 = np.array([ list(map(int,input().split())) for i in range(m) ]) 
a0 = np.dot(amat1,amat1)
print(np.dot(a0,amat1))