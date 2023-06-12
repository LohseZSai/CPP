import pandas as pd
df = pd.DataFrame(pd.read_excel(r'C:\Users\Scott\Documents\Tencent Files\1172720089\FileRecv\2023_MCM-ICM_Problems\2023_MCM-ICM_Problems\Problem_C_Data_Wordle.xlsx'))
alist = [f'{i}tries' for i in range(1,8)]
#每一行的数据都画成表格
data = []
for i in df.iterrows():
    i = list(i)
    data.append(i[1][5:])
newdata = [dict(i) for i in data]
print(newdata)

# 获取字母和计数的列表
trys = list(newdata.keys())
counts = list(newdata.values())

# 创建一个条形图
fig, ax = plt.subplots()
ax.bar(trys, counts)

# 设置图表标题和坐标轴标签
ax.set_title('字母出现频率')
ax.set_xlabel('Letter')
ax.set_ylabel('Frequency')

# 自适应调整X轴标签的显示
plt.xticks(rotation=0, ha='center')

# 显示图表
plt.show()