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


sns.pairplot(data=boston_df, vars=["CRIM", "RM", "AGE", "LSTAT", "MEDV"], hue="CHAS", palette="Set1", markers="o", diag_kind="kde", plot_kws={"alpha": 0.5})
plt.suptitle("Pairplot of CRIM, RM, AGE, LSTAT, MEDV with CHAS hue", y=1.02)
plt.show()