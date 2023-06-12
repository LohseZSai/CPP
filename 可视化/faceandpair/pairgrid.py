import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.datasets import load_iris
import pandas as pd


# 加载 iris 数据集
iris = load_iris()
iris_data = iris.data
iris_target = iris.target
iris_feature_names = iris.feature_names

# 将 iris 数据集转为 DataFrame 格式
iris_df = pd.DataFrame(data=iris_data, columns=iris_feature_names)
iris_df['target'] = iris_target

# 使用 PairGrid 绘制散点图矩阵
g = sns.PairGrid(iris_df, hue='target')
g.map_diag(sns.histplot)
g.map_offdiag(sns.scatterplot)
g.add_legend()
plt.show()