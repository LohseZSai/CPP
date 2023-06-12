n = int(input())
content = list(map(int, input().split()))
asktimes = int(input())
prefix_sum = [0] * (n + 1)
#进行一个预处理,使得时间复杂度为O(n+asktimes),而原来的时间复杂度为o(nm)
for i in range(1, n + 1):
    prefix_sum[i] = prefix_sum[i - 1] + content[i - 1]
#这里，把每次前缀的和提前算出来，这样就不会每一次再重复计算了
askzone = [tuple(map(int, input().split())) for i in range(1, asktimes + 1)]
for i in askzone:
    print(prefix_sum[i[1]] - prefix_sum[i[0] - 1])

