import pandas as pd

df = pd.read_excel(r'C:\Users\Scott\Desktop\实验4数据.xlsx',sheet_name='平时作业成绩')
df_group = df.groupby('班级')
data = list(df_group)
#使用四个聚合后的数据绘图
for i in data:
    print(i[1])