import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

path = r'C:\Users\Scott\Desktop\imagine.xlsx'

df = pd.read_excel(path)

#计算相关系数矩阵

corr_matrix = df.corr()

mat = np.round(corr_matrix, 2)

# 绘制热力图
sns.heatmap(corr_matrix, cmap="YlGnBu", annot=True)

# 设置图表标题
plt.title("Correlation Heatmap")

# 显示图表
plt.show()





