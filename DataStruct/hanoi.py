#递归适用于整体隔离类分析的算法！！！
#递归类似于数学归纳法，
#递归不需要详细展开
#错误案例如下
# def hanoi(n, a, b, c):
#     #n 圆盘个数
#     #a 初始的桩
#     #b 经过的桩
#     #c 最后到的桩
#     if n > 0 :
#         #首先把n-1个圆盘从a经过c移动到b,调用自己
#         hanoi(n-1, a, c, b)
#         print('move from {} to {}'.format(a,b))
#         #再把第1个圆盘从a移到c
#         print('move from {} to {}'.format(a,c))
#         #最后把n-1个经过a移动到c
#         hanoi(n-1, b, a, c)
#         print('move from {} to {}'.format(b,c))

# print(hanoi(3,'A','B','C'))

#正确案例如下：
from timetest import *
# @cal_time
#这里演示一下装饰器的运用，用于计算时间，相当于函数套函数的意思
def hanoi(n,a,b,c):
    if n > 0:
        hanoi(n-1,a,c,b)
        print('move from {} to {}'.format(a,b)) #这个代表一片盘子
        hanoi(n-1,b,a,c)
print(hanoi(3,'A','B','C'))
        

# def hanoi(n, a, b, c):
#     #n 圆盘个数
#     #a 初始的桩
#     #b 经过的桩
#     #c 最后到的桩
#     if n > 0:
#         #首先把n-1个圆盘从a经过c移动到b,调用自己
#         hanoi(n-1, a, c, b)
#         #将第一个圆盘从a移动到c
#         print('move from {} to {}'.format(a, c))
#         #再把n-1个经过a移动到c
#         hanoi(n-1, b, a, c)
#         #将最后一个圆盘从b移动到c
#         print('move from {} to {}'.format(b, c))

# print(hanoi(3, 'A', 'B', 'C'))












