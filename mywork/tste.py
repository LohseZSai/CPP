from selenium.webdriver.common.by import By
from selenium import webdriver
import pprint
import time
# 使用selenium完整的完成以前单纯使用爬取一个步骤完成的任务
driver = webdriver.Edge(executable_path='C:/edgedriver_win64/msedgedriver.exe')
driver.get('https://www.jd.com/')
'''1  完成自己登录，手动验证的功能'''
#进行文件打开：密码读取
with open(r'C:\Users\23608\Desktop\账号密码.txt','r',encoding='gbk') as f:
    txts = [i.replace('\n','') for i in f.readlines()]
    username, password = txts[0], txts[1]
loginbutton = driver.find_element(By.XPATH,'//*[@id="ttbar-login"]/a[1]')
#点击登录按钮，进行登录操作
loginbutton.click()
loginbutton1 = driver.find_element(By.XPATH,'//*[@id="content"]/div[2]/div[1]/div/div[3]/a')
loginbutton1.click()

usernamebt = driver.find_element(By.XPATH,'//*[@id="loginname"]')
passwordbt = driver.find_element(By.XPATH,'//*[@id="nloginpwd"]')
#点击输入框，模拟键盘输入
usernamebt.click()
usernamebt.send_keys(username)
passwordbt.click()
passwordbt.send_keys(password)

loginokbt = driver.find_element(By.XPATH,'//*[@id="loginsubmit"]')
loginokbt.click()
#下面给出几秒进行手动验证！
time.sleep(10)
#接下来打开排行榜网站，爬取需要的具体数据
miaoshabutton = driver.find_element(By.XPATH,'//*[@id="J_seckill"]/div/div/a')
miaoshabutton.click()

'''2  下面是爬取的主体部分'''
names, values = [], []
# 首先找到按钮位置，并逐一点击，进行数据采集
for i in range(12):


    name = driver.find_elements(By.XPATH, f'//*[@id="super_seckill"]/div/ul/li[{i}]/a/h4')
    author = driver.find_elements(By.XPATH, f'//*[@id="super_seckill"]/div/ul/li[{i}]/div/span/span[{i}]/i')
    alist = [txt.text for txt in name]
    blist = [txt.text for txt in author]
    names.extend(alist)
    values.extend(blist)


driver.close()