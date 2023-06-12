import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from statsmodels.tsa.arima.model import ARIMA
from sklearn.metrics import mean_squared_error
import pandas as pd

# 数据导入
path = r'C:\Users\Scott\Documents\Tencent Files\1172720089\FileRecv\2023_MCM-ICM_Problems (2)\2023_MCM-ICM_Problems\Problem_C_Data_Wordle.xlsx'
df = pd.read_excel(path)
date = df['Date']
value = df.iloc[:, 3]
# 以下是一个基于ARIMA模型的时间序列预测案例
# 首先进行数据的清洗以及填充、格式转换
df['date'] = pd.to_datetime(df['Date'])
# 填充缺失值
df.fillna(method='ffill', inplace=True)
# 将数据转换为numpy数组类型
data = np.array(value)
# 拆分测试集与训练集
train_data = data[:287]  # 训练集80%
test_data = data[287:]  # 测试集20%
model = ARIMA(train_data, order=(1, 1, 1))
result = model.fit()
# 预测测试集
start = len(train_data)
end = len(train_data) + len(test_data) - 1
pred = result.predict(start=start, end=end, dynamic=False, typ='levels')

# 可视化预测结果
plt.plot(test_data)
plt.plot(pred, color='red')
plt.show()
