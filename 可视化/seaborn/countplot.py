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

sns.countplot(x="RAD", data=boston_df, hue="CHAS", palette="Set1", dodge=True)
plt.title("Countplot of RAD with CHAS hue")
plt.xlabel("RAD")
plt.ylabel("Frequency")
plt.legend(title="CHAS")
plt.show()