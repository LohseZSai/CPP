#本模块用于测试函数的运行时间
import time

def cal_time(func):
    def wrapper(*args, **kwargs):
        t1 = time.time()
        result = func(*args, **kwargs)
        t2 = time.time()
        print('{} running time: {} secs.'.format(func.__name__, t2 - t1))
        return result
    return wrapper