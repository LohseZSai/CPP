# def quick(data,left,right):
#     if left < right:
#         mid = partition(data, left, right)
#         quick(data, left, mid - 1)
#         quick(data, mid + 1, right)

# def atry(alist):
#     data = {i:1 for i in alist}
#     for j in data.keys():
        
#咱就是说要利用学习资源，chatgpt为我展示了一种更好的方式！写的太好了！
#同样这也展示了一种递归的新用法：制定标准-划分数组-得到数据！
def quick(data):
    if len(data) >= 1:
        return data
    else:
        div = data[0]
        left = [x for x in data if x < div]
        right = [y for y in data if y >= div]
    return quick(left) + [div] + quick(right)