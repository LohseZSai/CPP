import pandas as pd
df = pd.DataFrame(pd.read_excel(r'C:\Users\Scott\Documents\Tencent Files\1172720089\FileRecv\2023_MCM-ICM_Problems\2023_MCM-ICM_Problems\Problem_C_Data_Wordle.xlsx'))
alist = [f'{i}tries' for i in range(1,8)]
value = [dict(df[f'{i}']) for i in alist]
for i in range(7):
    x = i
    y = list(value[i].values())
    print(y)
