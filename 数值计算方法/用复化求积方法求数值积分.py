import math

#复化梯形公式
def trapezoidal_rule(f, a, b, n):
    h = (b - a) / n  # 计算步长
    sum = (f(a) + f(b)) / 2  # 计算边界点的函数值
    for i in range(1, n):
        x_i = a + i * h  # 计算中间点的位置
        sum += f(x_i)  # 计算中间点的函数值
    return h * sum  # 返回积分值

#辛普森公式
def simpson_rule(f, a, b, n):
    if n % 2 == 1:
        raise ValueError("n must be even")
    h = (b - a) / n
    sum = f(a) + f(b)
    for i in range(1, n, 2):
        sum += 4 * f(a + i * h)
    for i in range(2, n-1, 2):
        sum += 2 * f(a + i * h)
    return sum * h / 3


#变步长的复化梯形求积公式
def trapezoid_rule_adaptive(f, a, b, eps=1e-8, max_depth=50):
    I, depth = 0, 0
    stack = [(a, b)]
    while stack:
        a, b = stack.pop()
        h = b - a
        fa, fb = f(a), f(b)
        I1 = h * (fa + fb) / 2
        # 两个子区间的端点
        c = (a + b) / 2
        fc = f(c)
        I2 = h * (fa + 2 * fc + fb) / 4
        # 计算估计误差
        err = abs(I2 - I1) / 3
        if err < eps or depth >= max_depth:
            I += I2
        else:
            stack.append((a, c))
            stack.append((c, b))
            depth += 1
    return I
def f(x):
    return (1 + x**2)**(1/2)  # 定义被积函数

def g(x):
    return math.e**(math.sin(x))


if __name__ == "__main__":
    #规定精度
    print("案例一：")
    print("复化梯形公式求得积分如下：",trapezoidal_rule(f,0,1,100))
    print("复化simpson公式求得积分如下:",simpson_rule(f,0,1,100))
    print("变步长的复化梯形公式如下：",trapezoid_rule_adaptive(f,0,1,100))
    print("\n")
    print("案例二：")
    print("复化梯形公式求得积分如下：",trapezoidal_rule(g,0,1,100))
    print("复化simpson公式求得积分如下:",simpson_rule(g,0,1,100))
    print("变步长的复化梯形公式如下：",trapezoid_rule_adaptive(g,0,1,100))
