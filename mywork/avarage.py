import os 
import pandas as pd
averages,names = [],[]
newdf = pd.DataFrame({'城市':[],'2022':[]})
for curDir, dirs, files in os.walk(r"C:\Users\Scott\Desktop\数据清洗完"):
    for file in files:
        realpath = os.path.join(curDir, file)
        name = os.path.basename(realpath).split('.')[0]
        data = pd.read_csv(realpath, encoding = 'utf-8-sig')
        print('yes')
        average = sum(data.平米均价)/len(data.平米均价)
        newdf = newdf.append({'城市':name,'2022':int(average)},ignore_index=True)
f = r'C:\Users\Scott\Desktop\2017-2021省会、新一线城市房价均价.xlsx'
df = pd.read_excel(f,index_col='城市')
finaldf = pd.merge(df,newdf,on='城市')
finaldf.to_excel(r'C:\Users\Scott\Desktop\最终数据汇总.xlsx')
print('done!')
    