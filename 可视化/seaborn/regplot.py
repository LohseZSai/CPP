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

sns.regplot(x="RM", y="MEDV", data=boston_df, scatter=True, fit_reg=True, ci=95, color="blue", scatter_kws={"s": 50}, line_kws={"linestyle": "--", "color": "red"})
plt.title("Scatterplot with Regression Line of RM and MEDV")
plt.show()