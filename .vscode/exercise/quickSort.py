#一个快速排序的python版本，来理解算法
def QSort(alist):
    if len(alist) <= 1:
        return alist
    privot = alist[0]
    left = [x for x in alist if x < privot]
    middle = [x for x in alist if x == privot]
    right = [x for x in alist if x > privot]
    return QSort(left) + QSort(middle) + QSort(right)

alist = [4,6,2,7,9,5,10,1,8,3]
print(QSort(alist))