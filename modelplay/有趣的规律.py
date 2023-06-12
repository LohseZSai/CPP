import pandas as pd
path = r'C:\Users\Scott\Documents\Tencent Files\1172720089\FileRecv\2023_MCM-ICM_Problems (2)\2023_MCM-ICM_Problems\Problem_C_Data_Wordle.xlsx'
data = pd.read_excel(path)
data['50% out'] = data['1 try'] + data['2 tries'] + data['3 tries']
counts = 0
for i in data['50% out']:
    if i < 50:
        counts += 1
print(counts)