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

sns.distplot(boston_df['RM'], hist=True, kde=True, rug=False, color="purple", hist_kws={"edgecolor": "black"}, kde_kws={"shade": True})
plt.title("Distribution of RM")
plt.show()