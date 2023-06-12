#寻找0的位置并切片
def search_0(alist):
    for index,value in enumerate(alist):
        if value == 0:
            return alist[:index+1]



alist = list(map(int, input().split()))
re_alist = search_0(alist)
print(*((re_alist[::-1])[1:]))