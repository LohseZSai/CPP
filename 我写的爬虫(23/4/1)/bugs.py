from selenium.webdriver.common.by import By
from selenium import webdriver
import pprint
import time
import pandas as pd
import jieba
# 使用selenium完整的完成以前单纯使用爬取一个步骤完成的任务
driver = webdriver.Edge()
#有机纯牛奶
driver.get('https://item.jd.com/100038312444.html?bbtf=1#comment')
#到达网站界面
time.sleep(3)
words = []
def cratch():
    for i in range(1,11):                      
        txt = driver.find_element(By.XPATH,f'//*[@id="comment-0"]/div[{i}]/div[2]/p').text
        word = list(jieba.cut(txt.replace('\n','')))
        words.extend(word)


#主体，用于切换网页
for i in range(1,101):
    if i == 1:
        nextpagebutton = driver.find_element(By.XPATH,'//*[@id="comment-0"]/div[12]/div/div/a[8]')
    else:
        nextpagebutton = driver.find_element(By.XPATH,'//*[@id="comment-0"]/div[12]/div/div/a[8]')
    #切换到下一页                                   
    driver.execute_script("arguments[0].click();", nextpagebutton)
    time.sleep(1)
    cratch()
    print(f"finish {i} in 100")





words = pd.Series(words)
df = words.value_counts()
df.to_excel(r'C:\Users\Scott\Desktop\huhuhu.xlsx')
driver.close()


