n, m, k = map(int, input().split())
ans = [0] * (k + 1)
for i in range(n):
    a = list(map(int, input().split()))
    for j in range(m):
        ans[a[j]] += 1
print(*ans[1:])