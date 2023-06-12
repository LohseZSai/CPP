import pandas as pd
import numpy as np
path = r'C:\Users\Scott\Documents\Tencent Files\1172720089\FileRecv\词频.xlsx'
df = pd.read_excel(path).iloc[:,:2]
path2 = r'C:\Users\Scott\Documents\Tencent Files\1172720089\FileRecv\2023_MCM-ICM_Problems (2)\2023_MCM-ICM_Problems\Problem_C_Data_Wordle.xlsx'
newdf = pd.read_excel(path2)
wordlist = newdf['Word']
words_disapper = {}
for i in wordlist:
    if i in list(df['Column1']):
        row, col = np.where(df == i)
        words_disapper[i] = int(row[0])+1
        print('yes!')
print(words_disapper)


