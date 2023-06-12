from math import *

def fun1(x):
    return x**2 - 1

def fun2(x):
    return (10/(x+4))**(1/2)

def fun3(x):
    return (x+1)**(1/2)

if __name__ == "__main__":
    epx, x0 = eval(input()),  eval(input())
    anss = []
    while(len(anss)<1000):#判断迭代次数，如果大于1000次判定为迭代失败
        #ans = fun1(x0)
        #ans = fun2(x0)
        ans = fun2(x0)
        x0 = ans
        anss.append(ans)
        if len(anss) > 1:
            if abs(ans - anss[-2]) < epx: 
                break 
    print(f"最终的不动点计算为：{anss[-1]},迭代的步骤为{len(anss)}")
    
