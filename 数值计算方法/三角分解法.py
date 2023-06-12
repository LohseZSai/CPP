import numpy as np
#首先把矩阵变成行阶梯
#用递归实现的行阶梯形算法
def digui_on_angle(mat1,mat2,n,m):
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
        mat2[m-n:,m-n:] = mat1
        return digui_on_angle(mat1[1:,1:],mat2,n-1,m)

#核心函数，用于处理问题
def optimized_digui_on_angle(mat1,mat2,n,m):
    if n == 2:
        # 两行的情况
        bstar = mat1[1][0]/mat1[0][0]
        mat1[1] = -bstar * mat1[0] + mat1[1]
        mat2[m-2:m,m-2:m] = mat1
        mat2[-1][-2] = bstar
        return mat2
    else:
        # 多行的情况
        astars = mat1[1:,0]/mat1[0][0]
        mat1[1:] = -np.outer(astars, mat1[0]) + mat1[1:]
        mat2[m-n:,m-n:] = mat1
        mat2[m-n+1:m, m-n] = astars
        return optimized_digui_on_angle(mat1[1:,1:],mat2,n-1,m)

#化成最简形
def rref(matrix):
    matrix = np.array(matrix)
    lead = 0
    rowCount, columnCount = matrix.shape
    for r in range(rowCount):
        if lead >= columnCount:
            return matrix
        if matrix[r][lead] != 0:
            matrix[r] = matrix[r] / matrix[r][lead]
            for i in range(rowCount):
                if i != r:
                    matrix[i] = matrix[i] - matrix[i][lead] * matrix[r]
            lead += 1
    return matrix

#矩阵的输入 ： 阶数和矩阵本体
if __name__ == "__main__":
    print("请输入矩阵的行数：")
    n = int(input())
    print("请输入矩阵的每一行，输入完一行后点击回车")
    mat = [list(map(float,input().split())) for i in range(n)]
    mat = np.array(mat)
    matcopy = mat.copy()
    print("请输入待求线性方程组的列向量")
    new_column = np.array(list([int(input())] for i in range(n)))
    m = n;
    print("得出LU矩阵，进行储存")
    ourmatrix = optimized_digui_on_angle(mat,matcopy,n,m)
    print(ourmatrix)
    downmatrix = np.tril(ourmatrix,0)
    onmatrix = np.triu(ourmatrix,0)
    np.fill_diagonal(downmatrix, val=1)
    matrix_with_new_column = np.hstack((downmatrix, new_column))
    print("下三角矩阵为：")
    print(downmatrix)
    print("上三角矩阵为：")
    print(onmatrix)
    matcopy2 = matrix_with_new_column.copy()
    mostresult = digui_on_angle(matrix_with_new_column,matcopy2,n,m)
    last_column = mostresult[:, -1].reshape(-1, 1)
    matrix_with_new_column2 = np.hstack((onmatrix, last_column))
    matcopy3 = matrix_with_new_column2.copy()
    result = digui_on_angle(matrix_with_new_column2,matcopy3,n,m)
    print("最后的结果为：")
    result = rref(result)
    print(result[:,-1].reshape(-1,1))
    