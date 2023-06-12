import matplotlib.pyplot as plt
from sklearn.datasets import load_boston

# 导入波士顿房价数据集
boston = load_boston()
data = boston.data
target = boston.target

# 将房价数据放入列表中
data_list = [target]

# 使用boxplot函数绘制箱线图
plt.boxplot(data_list, notch=True, sym='o', vert=True, patch_artist=True, labels=['House Prices'])

# 设置标题和轴标签
plt.title('Boston Housing Data - House Prices')
plt.xlabel('House Prices')
plt.ylabel('Value')

# 显示图像
plt.show()