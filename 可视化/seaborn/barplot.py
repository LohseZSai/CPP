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

sns.barplot(x="RAD", y="MEDV", data=boston_df, hue="CHAS", palette="Set1", ci=None)
plt.title("Barplot of RAD vs. MEDV with CHAS hue")
plt.xlabel("RAD")
plt.ylabel("MEDV")
plt.legend(title="CHAS")
plt.show()