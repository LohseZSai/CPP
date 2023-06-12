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

sns.heatmap(data=boston_df.corr(), annot=True, cmap="coolwarm", linewidths=0.5, cbar=True, square=True, mask=None)
plt.title("Heatmap of Correlation Matrix")
plt.show()