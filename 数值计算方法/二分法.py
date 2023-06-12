from sympy import *
import math
x = symbols('x')
f = log(E,x) - 0.5 + cos(x)
a, b = 1, 2
ypx = 0.00001
ff = diff(f,x)
while(abs(a - b) > ypx):
 mid = (a + b) / 2
 if ff.evalf(subs = {x:a}) > 0 and ff.evalf(subs = {x:b}) < 0 and ff.evalf(subs = {x:mid}) > 0 :
    a = mid 
 elif ff.evalf(subs = {x:a}) > 0 and ff.evalf(subs = {x:b}) < 0 and ff.evalf(subs = {x:mid}) < 0:
    b = mid
 elif ff.evalf(subs = {x:a}) < 0 and ff.evalf(subs = {x:b}) > 0 and ff.evalf(subs = {x:mid}) > 0:
    b = mid
 elif ff.evalf(subs = {x:a}) < 0 and ff.evalf(subs = {x:b}) > 0 and ff.evalf(subs = {x:mid}) < 0:
     a = mid 
     print((a+b)/2)
middy = (a + b) / 2
print(middy)
print(f'这是0.0000001的结果{f.evalf(subs = {x:middy})}')
