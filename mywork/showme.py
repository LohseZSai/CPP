import pandas as pd
import os
import numpy as np
from matplotlib import pyplot as plt
plt.rcParams['font.sans-serif']=['SimHei']


path = r'C:\Users\Scott\Desktop\最终数据汇总.xlsx'
data = pd.DataFrame(pd.read_excel(path))
geo_test_data=[]

namelist = list(data['城市'])
datalist = list(data['yes'])
for i in range(len(data.城市)):
 name = namelist[i]
 data = datalist[i]/400
 tuper = (name,data)
 geo_test_data.append(tuper)
from pyecharts import options as opts
from pyecharts.charts import Geo
from pyecharts.globals import ChartType,SymbolType

geo=Geo()
geo.add_schema(maptype='china')     #选定地图范围
geo.add('geo',geo_test_data,        #地图数据(列表数据)
        type_=ChartType.EFFECT_SCATTER,
        #'heatmap':热力图 ChartType.EFFECT_SCATTER:动态散点图
        symbol_size=15)
geo.set_series_opts(label_opts=opts.LabelOpts(is_show=False))    #是否显示数据标签
geo.set_global_opts(visualmap_opts=opts.VisualMapOpts(is_piecewise=False),   #是否显示图例
                                               #is_piecewise：图例是否分段
                   title_opts=opts.TitleOpts(title='Geo-基本示例')) #图形标题

geo.render('geo.html')   #保存为网页数据
geo.render_notebook()    #在notebook中显示