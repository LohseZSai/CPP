def lagrange(x_values, y_values, x):
    n = len(x_values)
    result = 0
    for i in range(n):
        term = y_values[i]
        for j in range(n):
            if j != i:
                term *= (x - x_values[j]) / (x_values[i] - x_values[j])
                
        result += term
    return result

def newtown(x_values, y_values, x):
    




if __name__ == "__main__":
    x_values = [1, 2, 3, 4]
    y_values = [1, 4, 9, 16]

    # 要插值的点
    x = 2.5
    print(lagrange(x_values,y_values,x))
    
    
    
    
    
    
    
    
    
    