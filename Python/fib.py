#用递归求斐波拉契数列
#最原始的方式
import numpy as np
def fib(n):
    if n == 1:
        return 1
    elif n == 2:
        return 1
    else:
        return fib(n-1) + fib(n-2)
# 使用数组存放数值
def fib1(n):
    arr = np.array([1,1])
    if n <= 2:
        return 1
    else:
        m = arr[n-3] + arr[n-2]
        arr.append(m)
    return arr[n-1]
print(fib1(3))
