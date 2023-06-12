# 下面用python实现求解集合的交、并、差、对称差集
print("请输入待求的两个集合：（每个元素以空格符号分割，输入完毕之后按回车结束，进行第二个集合的输入）")
A, B = list(map(eval, input().split())), list(map(eval, input().split()))
print("----------------------请输入想实现的功能----------------------------\n 0 求交集\n 1 求并集\n 2 求差集\n 3 求对称差集")
n = int(input())
# 求交集
if n == 0:
    print([i for i in A if i in B])
# 求并集
elif n == 1:
    print([i for i in set(A + B)])
# 求差集
elif n == 2:
    print([i for i in A if i not in B])
# 求对称差集
elif n == 3:
    C = set(A + B)
    D = [i for i in A if i in B]
    print([i for i in C if i not in D])
else:
    print("输入错误!")
