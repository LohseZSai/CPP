import pandas as pd
path = r'C:\Users\Scott\Documents\Tencent Files\1172720089\FileRecv\2023_MCM-ICM_Problems (2)\2023_MCM-ICM_Problems\Problem_C_Data_Wordle.xlsx'
data = pd.read_excel(path)
df1 = pd.DataFrame([row for _, row in data.iterrows() if len(set(row['Word'])) == len(row['Word'])])
df2 = pd.DataFrame([row for _, row in data.iterrows() if len(set(row['Word'])) != len(row['Word'])])
# for i in data.iterrows():
#     word = i[1].Word
#     if len(list(set(word))) == len(list(word)):
#         df.append(pd.Series(i[1]),ignore_index=True)
df1.to_excel(r'C:\Users\Scott\Desktop\abc.xlsx')
df2.to_excel(r'C:\Users\Scott\Desktop\ebf.xlsx')

