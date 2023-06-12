import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.datasets import load_boston
import pandas as pd
# 导入波士顿房价数据集
boston = load_boston()
data = boston.data
target = boston.target

# 创建DataFrame
boston_df = pd.DataFrame(data, columns=boston.feature_names)
boston_df['MEDV'] = target

# 使用lineplot绘制折线图
sns.lineplot(x="RM", y="MEDV", data=boston_df)

# 设置标题和标签
plt.title("Lineplot of RM vs. MEDV")
plt.xlabel("RM")
plt.ylabel("MEDV")

# 显示图像
plt.show()