import matplotlib.pyplot as plt
from sklearn.datasets import load_boston

# 导入波士顿房价数据集
boston = load_boston()

# 获取数据集中的特征和标签
X = boston.data
y = boston.target

# 计算各类别的数量
categories = ['Category1', 'Category2', 'Category3']
values = [len(X[X[:, 5] < 4]), len(X[(X[:, 5] >= 4) & (X[:, 5] < 6)]), len(X[X[:, 5] >= 6])]

# 使用bar函数绘制柱状图
plt.bar(categories, values, color='c', align='center')

# 设置标题和轴标签
plt.title('Distribution of RM')
plt.xlabel('RM')
plt.ylabel('Counts')

# 显示图像
plt.show()