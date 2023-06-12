d1, d2, n = map(int,input().split())
d = d2 - d1
alist = list(range(d1, (d2 + d*(n-1))+1, d))[:n]
print(sum(alist))
