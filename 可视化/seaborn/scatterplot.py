import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd
from sklearn.datasets import load_boston

# 导入波士顿房价数据集
boston = load_boston()
data = boston.data
target = boston.target

# 创建DataFrame
boston_df = pd.DataFrame(data, columns=boston.feature_names)
boston_df['MEDV'] = target

# 使用scatterplot绘制散点图
sns.scatterplot(x="RM", y="MEDV", data=boston_df)

# 设置标题和标签
plt.title("Scatterplot of RM vs. MEDV")
plt.xlabel("RM")
plt.ylabel("MEDV")

# 显示图像
plt.show()