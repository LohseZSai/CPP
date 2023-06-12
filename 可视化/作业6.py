#   1）分别统计不同专业班级及教学班级各项成绩的分布特点，并比较说明不同专业班级的差异；
#   2）分析期末考试成绩中七个小题成绩，比较说明各题的难度特点；（直方图）
#   3）分析期末考试成绩与六次平时作业的相关性；(热力图)
#   4）选择适当指标对全体学生进行聚类。



import pandas as pd
#完成数据的导入,并适当处理数据
df_totalscore = pd.read_excel(r'C:\Users\Scott\Desktop\实验4数据.xlsx',sheet_name='成绩汇总 ')
df_finalexam = pd.read_excel(r'C:\Users\Scott\Desktop\实验4数据.xlsx',sheet_name='期末成绩')
df_timescore = pd.read_excel(r'C:\Users\Scott\Desktop\实验4数据.xlsx',sheet_name='平时作业成绩')
df_totalscore = df_totalscore.iloc[1:,:]

df_totalscore.fillna(0)
df_timescore.fillna(0)
df_finalexam.fillna(0)