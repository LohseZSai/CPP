a, b ,n= [0,0,0,1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,0,1,1,1,0,1,0,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,1],[1,0,0,0,0,0,0,1,1,0,1,1,0,1,1,1,0,0,0,1,1,0,1,1,1,1,1,1,1,0,0,1,0,0,1,0,1,0,1,0,1,1,1,0,1,0],0
while(True):
    i,j = 0,0
    if a[i] == b[j]:
        a.pop(0)
        b.pop(0)
    else:
        c = a.pop(0)
        a.append(c)
    n += 1
    if len(a) == 0 :
        print(0)
        break
    if n>10000:
        break 
print(len(a))
        

