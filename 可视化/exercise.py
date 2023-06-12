import pandas as pd
from matplotlib import pyplot as plt
df = pd.read_csv(r'C:\Users\Scott\Downloads\archive\Cancer_Data.csv')
df = df.iloc[:,:32]#去掉空行

#plot方法及其使用
x = list(df.id)
sym = [str(i) for i in x]
y = df.radius_mean
# # 绘制图形
# fig, ax = plt.subplots()
# ax.plot(y, linewidth=2.0)
# # 显示图形
# plt.show()


#scatter方法及其应用
fig, ax = plt.subplots()
ax.scatter(y, linewidth=2.0)
plt.show()
























