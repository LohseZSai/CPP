import pandas as pd
df = pd.read_csv(r'C:\Users\Scott\CPP\pandas练习\练习.csv')
#练习1 提取其中的一列数据，并统计该列数据的最大值、最小值、平均值和中位数。
# print(df.Month.describe())

#练习2 提取其中的两列数据计算他们的相关系数
# print(df.Month.corr(df['Sales']))

# 练习3 计算其中一列数据的平均值，并将该列中小于平均值的数赋值为0，大于平均值的数赋值为1，并输出修改后的数据
# average = df['Sales']/len(df['Sales'])错误！这个做法是得到了一个series
# average = df['Sales'].mean()
#直接用df['Sales'].mean()就可以求得均值
# df[df['Sales'] < average] = 0
# df[df['Sales'] > average] = 1
# print(df)

# 练习4：使用 insert() 方法，在 Pandas DataFrame 中插入一列数据，并将该列数据设置为 DataFrame 的索引。
# df.insert(2,'total',df.sum(1))
# df = df.set_index('total')
# #注意该处的1意思就是横向，0是纵向
# print(df)
# 练习5：使用 where() 方法，在 Pandas DataFrame 中将符合条件的值替换为另一个值。
# df = df.where(df.Sales > 200, '合格')该行会把不满足条件的df.Sales中>100的一行全部替换成合格
# df.Sales = df.Sales.where(df.Sales>200, '不合格')
# print(df)
# 练习6：使用 mask() 方法，在 Pandas DataFrame 中将不符合条件的值替换为另一个值。
# 略
# 练习7：使用 lookup() 方法，在 Pandas DataFrame 中查找指定行和列对应的值。
# print(df.lookup([1],['Month']))
# 练习8：使用 eval() 方法，在 Pandas DataFrame 中计算新列的值，将其添加到 DataFrame 中。