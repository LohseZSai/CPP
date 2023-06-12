import time 
def fun3(f):
    def inner(*arg, **key):
        print(arg)
        t = time.time()
        r = f(*arg, **key)
        print(time.time() - t)
        return r
    return inner

@fun3
def fun(n=10):
    for i in range(n):
        j = i*2
    return j

@fun3 
def fun2(n):
    s = ''
    for i in range(n):
        s += str(i)
    print(s)

print(fun(n=100000))
print(fun2(100000))