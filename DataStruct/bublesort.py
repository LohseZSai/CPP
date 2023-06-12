
def bublesort(lst):
    for i in range(len(lst)-1): #一共n-1趟
        for j in range(len(lst)-1-i):
            if lst[j] > lst[j+1]:
                lst[j], lst[j+1] = lst[j+1], lst[j]
    return lst

alist = [4,5,6,1,2,7,9]
new = bublesort(alist)
print(new)

