
# 数据准备
data = pd.read_excel(r"C:\Users\Scott\Documents\Tencent Files\1172720089\FileRecv\2023_MCM-ICM_Problems (2)\2023_MCM-ICM_Problems\Problem_C_Data_Wordle.xlsx", index_col=0, parse_dates=True)
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from statsmodels.tsa.arima.model import ARIMA
from scipy import stats

# 模型拟合
model = ARIMA(data, order=(1, 1, 1))
result = model.fit()

# 预测
forecast_date = pd.to_datetime("2023-03-01")
forecast_result = result.forecast(steps=1)

# 计算标准误差
std_err = np.sqrt(result.mse)

# 计算置信区间
n = len(data)  # 样本大小
t_value = stats.t.ppf(1 - 0.05/2, n - 1)  # 计算t分布值
lower_bound = forecast_result[0] - t_value * std_err  # 下限
upper_bound = forecast_result[0] + t_value * std_err  # 上限

# 输出结果
print(f"The forecast value for March 1st, 2023 is {forecast_result[0]:.2f}.")
print(f"The 95% confidence interval for March 1st, 2023 is [{lower_bound:.2f}, {upper_bound:.2f}].")

# 绘制置信区间图
fig, ax = plt.subplots(figsize=(8, 5))
data.plot(ax=ax)
ax.axvline(x=forecast_date, color='r', linestyle='--')
ax.axhline(y=lower_bound, color='b', linestyle='--', label="95% confidence interval")
ax.axhline(y=upper_bound, color='b', linestyle='--')
ax.fill_betweenx(y=[lower_bound, upper_bound], x1=forecast_date, x2=data.index[-1], color='b', alpha=0.2)
ax.legend()
ax.set_xlabel("Date")
ax.set_ylabel("Value")
ax.set_title("Forecast and 95% confidence interval")
plt.show()