from sympy import *

def half_search_answer(f,a,b,epx):
    mid = (a + b) / 2
    ff = diff(f,x)
    fa = ff.evalf(subs = {x:a})
    fb = ff.evalf(subs = {x:b})
    fmid = ff.evalf(subs = {x:mid})
    while abs(a - b) > epx:
        mid = (a + b) / 2
        fa, fb, fmid = ff.evalf(subs={x:a}), ff.evalf(subs={x:b}), ff.evalf(subs={x:mid})
        if fa > 0 and fb < 0 and fmid > 0:
            a = mid 
        elif fa > 0 and fb < 0 and fmid < 0:
            b = mid
        elif fa < 0 and fb > 0 and fmid > 0:
            b = mid
        elif fa < 0 and fb > 0 and fmid < 0:
            a = mid 

    midy = (a + b) / 2
    print(f'这是0.0000001的结果{f.evalf(subs={x:midy})}')












if __name__ == "__main__":
    x = symbols('x')
    f = x**3 - 7*x + 3
    half_search_answer(f,1,2,10e-6)
    














