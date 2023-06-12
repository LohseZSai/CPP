from timetest import cal_time

@cal_time
def linear_search(li, val): #顺序查找
    for ind, v in enumerate(li):
        if v == val:
            return ind
    else:
        return None

@cal_time
def binary_search(li, val): #二分查找
    left, right = 0, len(li)-1
    while(left <= right):
        mid = (left + right) // 2
        if li[mid] == val:
            return mid
        elif li[mid] < val:
            left = mid + 1
        else:
            right = mid - 1
    else:
        return None 

alist = list(range(10000))
linear_search(alist, 721)
binary_search(alist, 721)