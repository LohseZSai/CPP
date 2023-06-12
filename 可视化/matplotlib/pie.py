import matplotlib.pyplot as plt

# 生成数据
labels = ['A', 'B', 'C', 'D']
values = [20, 30, 25, 15]
colors = ['red', 'green', 'blue', 'yellow']

# 使用pie函数绘制饼图
plt.pie(values, labels=labels, colors=colors, autopct='%1.1f%%', shadow=True, startangle=90)

# 设置标题
plt.title('Pie Chart Example')

# 显示图像
plt.show()