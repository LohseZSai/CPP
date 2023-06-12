import seaborn as sns
import matplotlib.pyplot as plt

# 导入数据集
boston_df = sns.load_dataset('tips')

# 创建FacetGrid对象
g = sns.FacetGrid(boston_df, col='day', hue='sex', height=4)

# 绘制图形
g.map(sns.scatterplot, 'total_bill', 'tip')
g.add_legend()

# 设置标题和标签
g.fig.suptitle('Total Bill vs. Tip by Day and Gender', y=1.05)
plt.xlabel('Total Bill')
plt.ylabel('Tip')

# 显示图形
plt.show()