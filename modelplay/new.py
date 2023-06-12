from matplotlib.dates import DateFormatter
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from statsmodels.tsa.arima.model import ARIMA
from datetime import datetime, timedelta
from statsmodels.stats.outliers_influence import summary_table

# 数据导入
path = r'C:\Users\Scott\Documents\Tencent Files\1172720089\FileRecv\2023_MCM-ICM_Problems (2)\2023_MCM-ICM_Problems\Problem_C_Data_Wordle.xlsx'

df = pd.read_excel(path, index_col=0)

# 填充缺失值
df.fillna(method='ffill', inplace=True)

# 定义窗口大小
window_size = 30

# 创建空列表存储预测值
forecasted_values = []

# 使用平滑窗口方法进行预测
for i in range(len(df) - window_size + 1):
    # 取出当前窗口的数据
    data = np.array(df.iloc[i:i + window_size])

    # 拆分训练集和测试集
    train_data = data[:-1]  # 前29天作为训练集
    test_data = data[-1]  # 最后一天作为测试集

    # 训练ARIMA模型
    model = ARIMA(train_data, order=(1, 1, 1))
    result = model.fit()

    # 预测测试集的值
    forecasted_value = result.forecast(steps=1)

    # 将预测值添加到列表中
    forecasted_values.append(forecasted_value[0])
    
# 预测2023年3月1日的数据
start_date = datetime(2023, 3, 1) - timedelta(days=1)  # 填充前一天的数据
end_date = datetime(2023, 3, 1)
test_data = np.array(forecasted_values[:-1])
model = ARIMA(test_data, order=(1, 1, 1))
result = model.fit()
forecasted_value = result.forecast(steps=1)
forecasted_values.append(forecasted_value)
#前59个值是1月1日到2月28日的预测值
#后29个值是3月1日到3月29日的预测值
start_date = '2023-01-01'
end_date = '2023-03-01'
index = pd.date_range(start=start_date, end=end_date, freq='D')
s = forecasted_values[:60]
forecasted_value = forecasted_values[59]#3月1日
print(forecasted_values[60:65])
# 构造 DataFrame 对象
jtof = pd.DataFrame({'Date': index, 'Number of  reported results': s})
# df2 = pd.concat([jtof,df], axis=0)
# df2.sort_values('Date', inplace=True)
# df2.to_excel(r'C:\Users\Scott\Desktop\yex.xlsx')
# #绘制actual图像


# # 可视化预测结果
# fig, ax = plt.subplots()
# ax.plot(df.index, df.values, label='Actual data')
# ax.plot(df2.index[-60:], df2[-60:], label='prediction')
# # 设置x轴刻度格式化器
# date_form = DateFormatter("%Y-%m")
# ax.xaxis.set_major_formatter(date_form)

# # 自动旋转x轴刻度
# plt.xticks(rotation=30)

# # 添加图例
# plt.legend()

# # 显示图形
# plt.show()

# 计算预测值的标准误差和置信区间
import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd

data = jtof
x = data["Date"].values.astype(float)
y=data['Number of  reported results']


#作图
fig = plt.figure(figsize=(10,6))
fig.patch.set_facecolor('white')
fig.patch.set_alpha(1)#设置透明度
#关键代码
sns.regplot(x=x, y=y, ci=95)#ci是置信区间，此处设置为95%
#xy标签设置
plt.ylabel('Number of reported results', fontdict={'family' : 'Times New Roman', 'size':12})
plt.xlabel('Date', fontdict={'family' : 'Times New Roman', 'size':12})
plt.xticks(fontproperties = 'Times New Roman', size = 12)
plt.yticks(fontproperties = 'Times New Roman', size = 12)
plt.show()
# 可视化预测值和置信区间
#计算3月1日的置信区间 ，3月1日的值：forecasted_value

#进行模型的评估
# import numpy as np

# def evaluate(y_true, y_pred):
#     mae = np.mean(np.abs(y_true - y_pred))
#     mse = np.mean(np.square(y_true - y_pred))
#     rmse = np.sqrt(mse)
#     mape = np.mean(np.abs((y_true - y_pred) / y_true))
#     return mae, mse, rmse, mape

# y_true = df['results']
# y_pred = df2['results'][:-60]
# mae, mse, rmse, mape = evaluate(y_true, y_pred)
# print("MAE: ", mae)
# print("MSE: ", mse)
# print("RMSE: ", rmse)
# print("MAPE: ", mape)