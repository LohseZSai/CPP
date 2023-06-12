a = [[1,2,3],[4,5,6],[7,8,9]]
n = len(a)
#通过规定方向实现顺时针打印
for i in zip(range(n)):
    for j in zip(range(n)):
        if i != n:
            print(a[i][j])

    
