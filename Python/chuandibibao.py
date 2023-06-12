import numpy as np
n= int(input())
amat1 = [[0]*n for k in range(n)]
R = [(1,3),(1,5),(2,5),(4,5),(5,4),(6,3),(3,2)]
for i,j in R:
    amat1[i-1][j-1] = 1
# print(np.array(amat1))
print(np.dot(amat1,amat1))
