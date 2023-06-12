import numpy as np
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

# Here is a sample matrix and how to use the function:

matrix = [[1, 2, -1, -4], [2, 3, -1, -11], [-2, 0, -3, 22]]
print("Original matrix:")
for row in matrix:
    print(row)
matrix = rref(matrix)
print("RREF:")
for row in matrix:
    print(row)
