import matplotlib.pyplot as plt
import numpy as np

# 生成随机数据
np.random.seed(0)
data = np.random.randn(1000) # 生成1000个随机数

# 使用hist函数绘制直方图
plt.hist(data, bins=30, color='skyblue', alpha=0.8, label='Data Distribution')

# 设置标题和轴标签
plt.title('Histogram Example')
plt.xlabel('Value')
plt.ylabel('Frequency')

# 添加图例
plt.legend()

# 显示图像
plt.show()