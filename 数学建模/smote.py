import pandas as pd
import numpy as np
from imblearn.combine import SMOTEENN
from sklearn.model_selection import train_test_split


df = pd.read_excel(r'C:\Users\Scott\Desktop\电工杯\有序数据处理完.xlsx')

X = df.drop('1、您的性别(1-22题为单选题)', axis=1).values  # 替换'target'为你的目标列名
y = df['1、您的性别(1-22题为单选题)'].values  # 替换'target'为你的目标列名

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

smote_enn = SMOTEENN(random_state=4)
X_resampled, y_resampled = smote_enn.fit_resample(X_train, y_train)

print("Resampled X:\n", X_resampled)
print("Resampled y:\n", y_resampled)

# 将重采样后的数组转换为DataFrame
resampled_df = pd.DataFrame(data=np.concatenate((X_resampled, y_resampled.reshape(-1, 1)), axis=1), columns=df.columns)

resampled_df.to_excel(r'C:\Users\Scott\Desktop\电工杯\smote算法.xlsx')


