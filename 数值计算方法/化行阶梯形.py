import numpy as np


#首先把矩阵变成行阶梯

#用递归实现的算法
def hangjieti_on_digui(mat1,mat2,n,m):
    if n == 2:
        for i in range(1,n):
            bstar = mat1[i][0]/mat1[0][0]
            mat1[i] = -bstar * mat1[0] + mat1[i]
        mat2[m-2:,m-2:] = mat1
        return mat2
    else:
        for i in range(1,n):
            astar = mat1[i][0]/mat1[0][0]
            mat1[i] = -astar * mat1[0] + mat1[i]
        lie = len(list(zip(*mat)))
        mat2[m-n:,m-n:] = mat1
        return hangjieti_on_digui(mat1[1:,1:],mat2,n-1,m)



#矩阵的输入 ： 阶数和矩阵本体
if __name__ == "__main__":
    n = int(input())
    mat = [list(map(float,input().split())) for i in range(n)]
    # m = len(list(zip(*mat)))
    m = n
    mat = np.array(mat)
    matcopy = mat.copy()
    #m应该为矩阵的列的数目
    print(hangjieti_on_digui(mat,matcopy,n,m))
    