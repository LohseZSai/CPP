# 1使用pipe()方法对iris数据集进行标准化处理，
# 并返回一个新的DataFrame。

#标准化处理的流程：身高和体重的例子
# 计算身高和体重特征的均值和标准差。
# 对于每个观测值，用身高减去身高的均值，然后除以身高的标准差。这样就得到了标准化后的身高特征。
# 对于每个观测值，用体重减去体重的均值，然后除以体重的标准差。这样就得到了标准化后的体重特征。
# 这就是在这个例子中进行标准化的方法。
# from sklearn.preprocessing import StandardScaler
# def  standardize(df): 
#     scaler = StandardScaler() 
#     scaled_df = scaler.fit_transform(df) 
#     return pd.DataFrame(scaled_df, columns=df.columns) 

# import pandas as pd
# from sklearn.datasets import load_iris
# iris = load_iris()
# df = pd.DataFrame(iris.data, columns = iris.feature_names)
# df2 = df.pipe(standardize)
# print(df,df2)


# 2使用apply()方法计算tips数据集中每一行的小费比例，
# 并创建新列"tip_pct"。

#调用tips数据集
import pandas as pd
import seaborn as sns
tips=sns.load_dataset('tips')
# tips['tip_pct'] = tips.apply(lambda s:s.tip/s.total_bill, axis=1)
# print(tips)



#3 使用map()方法将tips数据集中的"sex"列和"smoker"列转换为数值类型，
# # 并创建新列"sex_num"和"smoker_num"。
# import pandas as pd
# import seaborn as sns

# # 加载 tips 数据集
# tips = sns.load_dataset("tips")

# # 定义 sex 和 smoker 列的映射字典
# sex_map = {"Male": 0, "Female": 1}
# smoker_map = {"Yes": 1, "No": 0}

# # 使用 map() 方法将 sex 和 smoker 列转换为数值类型
# tips["sex_num"] = tips["sex"].map(sex_map)
# tips["smoker_num"] = tips["smoker"].map(smoker_map)

# # 返回转换后的 Dataframe
# print(tips)
# #可以看到map的作用是通过传入的字典完成映射！！！！！



# 4使用agg()方法计算tips数据集中按照性别和是否吸烟分组后的小费比例的
# 均值、标准差和最大值，并返回一个新的DataFrame。
# tips['tip_pct'] = tips.apply(lambda s:s.tip/s.total_bill, axis=1)
# new_df = tips.groupby(['sex','smoker']).agg({'tip_pct':['max','mean','std']})
# print(new_df)