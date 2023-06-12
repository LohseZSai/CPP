# coding:utf-8
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

plt.rcParams["font.sans-serif"] = ["SimHei"]
plt.rcParams["axes.unicode_minus"] = False
# 确保可以正常显示中文和负号

df = pd.read_csv(r"C:\Users\Scott\Documents\Tencent Files\1172720089\FileRecv\中国2012年至2021年这十年内的财政支出.csv", index_col=[0])
# 读取爬取后的生成的csv文件
year = [2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019, 2020, 2021]
# 设置面积堆积图的横坐标
years = ['2012年', '2013年', '2014年', '2015年', '2016年', '2017年', '2018年', '2019年', '2020年', '2021年']
# 设置面积堆积图的横坐标的标签，即年份
money = ['中央财政支出', '地方财政支出', '社保支出', '国防支出']
# 设置不同的面积堆积图的标题，并爬取不同的数据
labellist = ['中央财政支出', '地方财政支出', '社保支出', '国防支出']
# 设置横坐标的标签列表
colorlist = ["blue", "green", "yellow", "red"]
# 设置面积堆积图的颜色

plt.figure(figsize=(20, 10), dpi=80)
# 设置图表的尺寸和分辨率
ax1 = plt.subplot2grid((2, 1), (0, 0))
# 绘制柱形图
ax2 = plt.subplot2grid((2, 1), (1, 0))
# 绘制堆积柱形图
# 第四种绘制子图的方式，即利用subplot2grid绘制子图
data = list()
# 设置存储列表，为后续的制作柱形堆积图做准备
for i in range(0, len(money)):
    Y = list()
    for t in df.loc['2012年':'2021年', money[i]]:
        Y.append(t)
    data.append(Y)
# 做好数据准备工作
ax1.stackplot(year, data, baseline='zero', colors=colorlist, labels=labellist, alpha=0.3)
# 绘制面积堆积图
ax1.grid(visible='both', which='both', axis='both', linewidth=1, color='purple', alpha=0.3)
ax1.set_title('中国2012年至2021年这十年内的财政支出')
ax1.set_ylabel('财政支出/万亿元')
ax1.set_xlabel("年份")
# 标签显现

ax2.stackplot(year, range(len(data[0])), *data, colors=colorlist, labels=labellist, alpha=0.3,
              baseline='weighted_wiggle')
# 绘制量化波形图
ax2.grid(visible='both', which='both', axis='both', linewidth=1, color='purple', alpha=0.3)
ax2.set_ylabel('财政支出/万亿元')
ax2.set_xlabel("年份")
ax2.set_xticks(year, years)
# 设置标签，标题
ax2.legend(fontsize=10, loc="upper right")
# 标签显现
plt.show()
