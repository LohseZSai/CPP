# import datetime
# alist = list(range(1970, datetime.datetime.now().year))
# date = 0
# for i in alist:
#    if i % 400 == 0:
#       date += 366
#    elif i % 4 == 0 and i % 100 != 0:
#       date += 366
#    else:
#       date += 365
# print('过去了{}天{}小时'.format(date,datetime.datetime.now().hour))

# import datetime
# def leap(year):
#    if year % 400 == 0 or year % 4 == 0 and year % 100 != 0:
#       return True
#    else:
#       return False

# def daysfrom1970():
#    days = [31,28,31,30,31,30,31,31,30,31,30,31]
#    year = datetime.datetime.now().year
#    month = datetime.datetime.now().month
#    day = datetime.datetime.now().day
#    result = 0
#    for i in range(1970,year):
#       result += 365
#       if (leap(i)):
#          result += 1
#    for j in range(1, month):
#       result += days[j]
#    result += day
#    print(result)
# daysfrom1970()


# alist = list(map(int, input().split()))
# if len(alist) % 2 == 0:
#    sorted(alist, reverse=True)
#    print(min(alist[(len(alist)//2) - 1], alist[len(alist)//2]))
# else:
#    print(alist[(len(alist)//2)])

# def main():
#    n = int(input())
#    res = 0
#    ress = []
#    for i in range(1,n+1):
#       revers = int(str(i)[::-1])
#       if str(i)[0] == '0':
#          revers = revers[1:]
#       if i % revers == 0:
#          res += 1

#    print(res)



# if __name__ == '__main__':
#     main();



# def fun(a,b):
#     if a == 1:
#         return C*b + D
#     else:
#         return fun(a - 1, fun(a - 1, b))
# def main():
#     vals = list(map(int, input().split()))
#     a, b = vals[0], vals[1]
#     global C, D
#     C, D = vals[2], vals[3]
#     print(int(str(fun(a,b))[-1]))


# if __name__ == '__main__':
#     main();

def cor(x,y):
   for i in barrs:
      if (x,y) !=  i:
         return True
      else:
         False


n, m = map(int, input().split())
x, y = map(int, input().split())  #初始位置
k = int(input())
gamemap = [[0 for col in range(m)] for row in range(n)]
barrs = []
for i in range(k):
   barr = list(map(int, input().split()))
   barrs.append((barr[0],barr[1]))
   gamemap[barr[0]-1][barr[1]-1] = 1
move = input()
for i in move:
   if i == 'R' and cor(x,y+1) is True:#向右走，列数+1
      y += 1
   elif i == 'L' and cor(x,y-1) is True:#左
      y -= 1
   elif i == 'D' and cor(x-1,y) is True:#下
      x += 1
   elif i == 'U' and cor(x+1,y) is True:#上
      x -= 1
print(x,y)
   
pass


