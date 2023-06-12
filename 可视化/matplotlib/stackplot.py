import matplotlib.pyplot as plt

# 生成数据
x = [1, 2, 3, 4, 5]
y1 = [1, 3, 2, 4, 5]
y2 = [2, 3, 1, 4, 3]
y3 = [3, 1, 4, 2, 1]

# 使用stackplot函数绘制堆叠区域图
plt.stackplot(x, y1, y2, y3, colors=['magenta', 'cyan', 'lime'], labels=['Y1', 'Y2', 'Y3'], alpha=0.7)

# 设置标题和轴标签
plt.title('Stackplot Example')
plt.xlabel('X')
plt.ylabel('Y')

# 添加图例
plt.legend()

# 显示图像
plt.show()