import pandas as pd
import pandas as pd
from collections import Counter
from wordcloud import WordCloud


#清洗数据
data = pd.DataFrame(pd.read_excel(r'C:\Users\Scott\Desktop\huhuhu.xlsx'))
# keep_rows = []
# for index,row in data.iterrows():
#     if len(row['词语']) != 1 and row['词语'] not in ['，','。','！','、','：']:
#         keep_rows.append(row)
# data = pd.DataFrame(keep_rows)


# 将数据中的所有单词都放入一个列表中
all_words = data.词语


# 计算每个单词的出现次数
word_counts = Counter(all_words)

# 生成词云
wordcloud = WordCloud().generate_from_frequencies(word_counts)


import matplotlib.pyplot as plt
import wordcloud as wc
import jieba
from PIL import Image
import numpy as np

text = " ".join(all_words)#用空格连接所有的词
mask = np.array(Image.open(r"C:\Users\Scott\Desktop\机器人4.png"))# 指定词云图效果
word_cloud = wc.WordCloud(background_color="white",font_path="msyh.ttc" , mask=mask) 
# 创建词云对象
word_cloud.generate(text)#生成词语
plt.imshow(word_cloud)#显示词云图
word_cloud.to_file(r"C:\Users\Scott\Desktop\yes.png")
#保存成图片
plt.show()# 显示图片
