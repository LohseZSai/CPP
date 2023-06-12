import pandas as pd
from sklearn.preprocessing import MinMaxScaler, StandardScaler

# 读取DataFrame数据
df = pd.read_excel(r'C:\Users\Scott\Desktop\电工杯\有序数据处理完.xlsx')

# 提取特征矩阵X和目标变量y
X = df.drop('1、您的性别(1-22题为单选题)', axis=1)  # 替换'1、您的性别(1-22题为单选题)'为你的目标列名
y = df['1、您的性别(1-22题为单选题)']  # 替换'1、您的性别(1-22题为单选题)'为你的目标列名

# 创建归一化对象
scaler = MinMaxScaler()  # 或者使用 StandardScaler()

# 对特征矩阵X进行归一化
X_normalized = scaler.fit_transform(X)

# 将归一化后的特征矩阵X_normalized转换为DataFrame
df_normalized = pd.DataFrame(data=X_normalized, columns=X.columns)

# 将归一化后的特征矩阵df_normalized与目标变量y合并
df_normalized['1、您的性别(1-22题为单选题)'] = y

df_normalized.to_excel(r'C:\Users\Scott\Desktop\电工杯\归一化数据.xlsx')