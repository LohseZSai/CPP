import numpy as np

def compare_to_end(column1,column2,eps):
    i = len(column1)
    for k in range(i):
        cha = abs(column1[k] - column2[k])
        if cha > eps:return False
    return True
        

def Jacob_calculate(mat,result_column,eps):
    x0 = np.zeros(len(mat))
    x0 = x0[:,np.newaxis]
    matD = np.diag(np.diag(mat))
    matR = -np.tril(mat)
    np.fill_diagonal(matR, 0)
    matL = -np.triu(mat)
    np.fill_diagonal(matL, 0)
    #求D矩阵的逆矩阵
    results = []
    times = 0
    matD_inv = np.linalg.inv(matD)
    matB = np.dot(matD_inv,matL + matR)
    eigenvalues, _ = np.linalg.eig(matB)
    #求特征值、谱半径
    g = np.dot(matD_inv, result_column)
    eigenvalues = np.abs(eigenvalues)
    if(max(eigenvalues) < 1):print("jacobi法得出该矩阵收敛")
    else: print("jacobi法得出该矩阵收敛")
    while(times <= 30):
        times += 1;
        
        if times == 1:        
            xk = np.dot(matB, x0) + g
            results.append(xk)
        else:
            xknext = np.dot(matB, results[-1]) + g
            results.append(xknext)
        print(f"此时迭代{times}次，x{times}为{results[-1]}")
        if len(results) > 1 :
            if compare_to_end(results[-1],results[-2],eps) is True:
                return results[-1]




#矩阵的输入 ： 阶数和矩阵本体
if __name__ == "__main__":
    print("请输入矩阵的行数：")
    n = int(input())
    print("请输入矩阵的每一行，输入完一行后点击回车")
    mat = [list(map(float,input().split())) for i in range(n)]
    mat = np.array(mat)
    print("请输入待求线性方程组的列向量")
    new_column = np.array(list([int(input())] for i in range(n)))
    print("请输入eps的值：")
    eps = eval(input())
    print("该线性方程组的求解迭代过程如下：")
    result = Jacob_calculate(mat,new_column,eps)
    print("最终结果为：")
    print(result)
