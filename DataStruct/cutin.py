def cutin1(alist):
    for i in range(1,len(alist)-1):#第一张：摸到的牌，后面的：每次摸到的牌
        j = i - 1 #j指的是手里的牌的下标志
        while(alist[i] > alist[j]):
            alist[0:0] = (alist[j],)  #只实现了插入功能，没有删去
            alist.remove(alist[j])
    return alist

def cutin2(alist):
    for i in range(1,len(alist)):#第一张：摸到的牌，后面的：每次摸到的牌
        tmp = alist[i]
        j = i - 1 #j指的是手里的牌的下标志
        #思考：这一段是如何实现的？？
        while(j >= 0 and alist[j] >tmp):
            alist[j+1] = alist[j]
            j -= 1
        #上面这段循环是在找插入的位置
        alist[j+1] = tmp
    return alist

def cutin3(alist):
    for i in range(1, len(alist)):
        val = alist[i] #val是摸到的牌的下标
        j = i -1 #j是手里牌的下标
        #下面把摸到的牌在手里寻找合适的位置
        while(j >= 0 and val < alist[j]): #手里牌的下表不能小于0，即插入的顺序不可能为-1；另外一个条件是摸到的牌比手里的牌小，就交换顺序
            #条件真就循环
            alist[j],alist[j+1] = val, alist[j]#这里和原作有点不一样？
            j -= 1
    return alist

a = [3,2,4,1,5,7,9,6,8]
print(cutin3(a))