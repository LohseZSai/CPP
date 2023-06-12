

#此处是关于apply函数和pipe函数的使用
# import pandas as pd
# import numpy as np

# # 创建一个包含年龄、性别、身高、体重的DataFrame
# df = pd.DataFrame({"age": [20, 25, 30, 35],
#                    "gender": ["M", "F", "M", "F"],
#                    "height": [170, 165, 180, 175],
#                    "weight": [60, 55, 80, 65]})
# print(df)

# # 定义一个函数，将年龄增加10岁
# def add_age(x):
#     return x + 10

# # 定义一个函数，将身高和体重转换为英制单位
# def convert_units(df):
#     df["height"] = df["height"] * 0.393701 # 厘米转换为英寸
#     df["weight"] = df["weight"] * 2.20462 # 千克转换为磅
#     return df

# # 使用pipe方法对整个DataFrame应用convert_units函数
# df2 = df.pipe(convert_units)
# print(df2)

# # 使用apply方法对每一行应用add_age函数，并创建新列"age_new"
# df2["age_new"] = df2["age"].apply(add_age)
# print(df2)

# 如果你想使用apply函数对一行数据进行函数的操作，你需要指定axis参数为1，表示沿着列的方向进行操作。例如，如果你想计算每一行的身高和体重的比例，你可以这样写：

# 定义一个函数，计算身高和体重的比例
# def ratio(x):
#     return x["height"] / x["weight"]

# 使用apply方法对每一行应用ratio函数，并创建新列"ratio"
# df2["ratio"] = df2.apply(ratio, axis=1)
# print(df2)

# 如果对列操作：
# 使用apply方法对每一列应用np.mean函数，并创建新的Series
# mean = df2.apply(np.mean)
# print(mean)