import matplotlib.pyplot as plt
from sklearn.datasets import load_boston

# 导入波士顿房价数据集
boston = load_boston()

# 获取数据集中的特征和标签
X = boston.data
y = boston.target

# 使用scatter函数绘制散点图
plt.scatter(X[:, 5], y, c='b', s=20, marker='o', cmap='Blues')

# 设置标题和轴标签
plt.title('Boston House Prices')
plt.xlabel('RM')
plt.ylabel('Price')

# 显示图像
plt.show()