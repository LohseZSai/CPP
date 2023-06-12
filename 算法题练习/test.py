n = int(input())
world = list(map(int, input().split()))
m = max(world)
matrix = [[0] * n for _ in range(m)]
for index,value in enumerate(world):
    for i in range(value):
        matrix[i][index] = 1
zero_nums = 0
for i in range(m):
    row = matrix[i]
    ones_indices = [j for j in range(n) if row[j] == 1]
    if len(ones_indices) > 1:
        for j in range(len(ones_indices)-1):
            start_index = ones_indices[j]
            end_index = ones_indices[j+1]
            zeros_count = end_index - start_index - 1
            zero_nums += zeros_count
print(zero_nums)