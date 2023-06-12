#牛顿法,需给定伊普西隆和函数表达式
import math
from sympy import *
x = symbols('x')
f = 3 * x ** 2 - (math.e)**x
# f = (math.e)**x + 10*x - 2 
ff = diff(f,x)
fff = diff(ff,x)
x0 = 1#输入初始迭代点
ypx = 10e-6
flag = 0
anss = []
while(True):
 demy = (f.evalf(subs = {x:x0}))/(ff.evalf(subs = {x:x0}))
 x0 = x0 - demy
 anss.append(x0)
 flag += 1
 print(f"迭代第{flag}次，此时的x{flag}={x0}，函数值为{f.evalf(subs = {x:x0})}")
 if len(anss) > 1:
            if abs(x0 - anss[-2]) < ypx: 
                break 
#第一问为[1,2]，第二问为[0,2]
print(f"区间[0,2]上的根为{x0},带入函数表达式的值为{f.evalf(subs = {x:x0})},此时共迭代{flag}次")
