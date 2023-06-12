import pandas as pd

df = pd.read_excel(r'C:\Users\Scott\Documents\Tencent Files\1172720089\FileRecv\32732fc6-dd9e-40a7-8a9a-de0da4a42122\2023-51MCM-Problems\2023-51MCM-Problem B\附件1(Attachment 1)2023-51MCM-Problem B.xlsx')
df2 = pd.DataFrame()
for i in df.iterrows():
    if i[1][1] == 'M' and i[1][2] == 'U':
        df2 = df2.append(i[1])
print(df2)