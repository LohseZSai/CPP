import matplotlib.pyplot as plt
import numpy as np

# 生成数据
x = np.linspace(0, 10, 100)
y1 = np.sin(x)
y2 = np.cos(x)

# 使用fill_between函数绘制填充区域图
plt.fill_between(x, y1, y2, color='purple', alpha=0.3, label='Area between y1 and y2')

# 设置标题和轴标签
plt.title('Fill Between Example')
plt.xlabel('X')
plt.ylabel('Y')

# 添加图例
plt.legend()

# 显示图像
plt.show()