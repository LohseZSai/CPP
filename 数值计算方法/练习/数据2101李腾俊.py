
import math

#n为迭代次数，n0为迭代初始值
def Solve_the_question(n,n0):
    anss, times = [], 1
    anss.append(n0)
    while(times != n+1):
        Inext = 1/times - 8 * anss[-1]
        anss.append(Inext)
        print("第{}次迭代结果为I{}:{:.6f}".format(times,times,Inext))
        times += 1
    return anss

# 检验计算是否稳定
def check_the_mistake(anss):
    print(len(anss))
    checks = []
    for i in range(len(anss)):
        if(i != len(anss)-1):
            check = anss[i] - anss[i+1]
            checks.append(check)
        else:break
    for i in checks:
        print(i)


if __name__ == "__main__":
    anss = Solve_the_question(20,1/math.e**(-2))
    check_the_mistake(anss)