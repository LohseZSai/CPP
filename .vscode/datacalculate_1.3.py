import math
from sympy import *
def Fixed_Point_Iteration(f,x0,ypx):
    i = 0
    g = lambdify(x,f,'numpy')
    ans = []
    while(i<50):
        x1 = g(x0)
        ans.append(x1)
        if abs(x1-x0) < ypx:
            return {a:b for a,b in zip(list(range(1,i+1)),ans)}
        x0 = x1
        i += 1
    raise ValueError("Failed to converge within maximum iterations.")



if __name__ == "__main__":
    x = symbols('x')
    f1 = x**2 + 1
    f2 = 1 + 1/x
    f3 = (x + 1)**(1/2)

    print(Fixed_Point_Iteration(f1, 1,1e-10))
    print(Fixed_Point_Iteration(f2, 1,1e-10))
    print(Fixed_Point_Iteration(f3, 1,1e-10))