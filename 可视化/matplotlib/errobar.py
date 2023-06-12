import matplotlib.pyplot as plt
import numpy as np

# 生成数据
x = np.arange(0, 10, 1)
y = np.sin(x)
y_err = 0.2 * np.random.rand(len(x)) # 随机生成误差值

# 使用errorbar函数绘制带有误差线的图形
plt.errorbar(x, y, yerr=y_err, fmt='o', ecolor='red', capsize=3, label='Data with Error')

# 设置标题和轴标签
plt.title('Errorbar Example')
plt.xlabel('X')
plt.ylabel('Y')

# 添加图例
plt.legend()

# 显示图像
plt.show()