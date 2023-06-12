import matplotlib.pyplot as plt
from sklearn.datasets import load_boston

# 导入波士顿房价数据集
boston = load_boston()

# 获取数据集中的特征和标签
X = boston.data
y = boston.target

# 使用plot函数绘制一条线
plt.plot(y, label='Price')

# 设置图例和标题
plt.legend()
plt.title('Boston House Prices')

# 显示图像
plt.show()