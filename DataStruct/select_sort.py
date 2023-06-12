import random


#这里是较为复杂一点的插入排序
def select_sort1(alist):
    #创建新列表用于储存值  
    newone = []
    for i in range(len(alist)):
        #思路：弹出最小值的索引-添加入新列表-返回
        newone.append(alist.pop(alist.index(min(alist))))
    return newone
#注意，写算法的时候最好不用内置函数哦(index等)
def select_sort2(alist):
    newone = []
    for i in range(len(alist)):
        for j in alist:
            newval = min(alist)
            newone.append(newval)
            alist.remove(newval)     #使用remove索引会发生变化，不好
    return newone

def select_sort3(alist):
    for i in range(len(alist) - 1): #同冒泡排序的方法，最后一位不需要遍历
        min_loc = i
        for j in range(i + 1, len(alist) - 1):
            if alist[j] < alist[min_loc]:
                min_loc = j
        if min_loc != j:  #思考，为什么这一步要这么做？
            alist[i], alist[min_loc] = alist[min_loc], alist[i]
    return alist
        
def select_sort4(alist):
    for i in range(len(alist) - 1): #同冒泡排序的方法，最后一位不需要遍历
        min_loc = i
        for j in range(i + 1, len(alist) - 1):
            if alist[j] < alist[min_loc]:
                min_loc = j
        alist[i], alist[min_loc] = alist[min_loc], alist[i]
    return alist

# def selectdigui_sort5(alist):
#     wait to write
        







alist = [random.randint(1,100) for i in range(10)]
print(select_sort3(alist))