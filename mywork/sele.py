from selenium.webdriver.common.by import By
from selenium import webdriver
import pprint
import time
# 使用selenium完整的完成以前单纯使用爬取一个步骤完成的任务
driver = webdriver.Edge(executable_path='C:/edgedriver_win64/msedgedriver.exe')
driver.get('https://www.qidian.com/')
'''1  完成自己登录，手动验证的功能'''
# 进行文件打开：密码读取
with open(r'C:\Users\Scott\Desktop\账号何密码.txt', 'r', encoding='gbk') as f:
    txts = [i.replace('\n', '') for i in f.readlines()]
    username, password = txts[0], txts[1]
loginbutton = driver.find_element(By.XPATH, '//*[@id="login-btn"]')
# 点击登录按钮，进行登录操作
loginbutton.click()
iframe = driver.find_element(By.XPATH, '//*[@id="loginIfr"]')
# 此处注意，因为有些网站的登录页面是内嵌在网页本身的，需要进入iframe标签进行元素的再定位
driver.switch_to.frame(iframe)
usernamebt = driver.find_element(By.XPATH, '//*[@id="username"]')
passwordbt = driver.find_element(By.XPATH, '//*[@id="password"]')
# 点击输入框，模拟键盘输入
usernamebt.click()
usernamebt.send_keys(username)
passwordbt.click()
passwordbt.send_keys(password)
loginokbt = driver.find_element(
    By.XPATH, '/html/body/div[2]/div[2]/div/div[1]/div[1]/div[1]/div[1]/div[2]/a')
loginokbt.click()
# 下面给出几秒进行手动验证！
time.sleep(7)
# 接下来打开排行榜网站，爬取需要的具体数据
rankbutton = driver.find_element(
    By.XPATH, '/html/body/div[1]/div[4]/div/ul/li[3]/a')
rankbutton.click()
# 点击更多按钮，达到具体网站位置
morebutton = driver.find_element(
    By.XPATH, '/html/body/div[1]/div[6]/div[2]/div[2]/div/div[1]/h3/i/a')
morebutton.click()
'''2  下面是爬取的主体部分'''
names, authors = [], []
# 首先找到按钮位置，并逐一点击，进行数据采集
for i in range(12):
    # 首先必须点击三角按钮，才能进入月份的选择
    trianglebutton = driver.find_element(
        By.XPATH, '//*[@id="month"]/a/span[2]')  # 这里我发现必须每次都重新读取一次，不然爬了两页就要报错

    trianglebutton.click()
    button = driver.find_element(
        By.XPATH, f'//*[@id="-1"]/div[4]/ul/li[{i+1}]')
    button.click()
    name = driver.find_elements(By.XPATH, '//div/h2')
    author = driver.find_elements(By.XPATH, '//a[@class="name"]')
    alist = [txt.text for txt in name]
    blist = [txt.text for txt in author]
    names.extend(alist)
    authors.extend(blist)
driver.close()
# 浅浅的用过滤进行一下处理，洗去空数据
authors = list(filter(lambda s: s != '', authors))
rezult = [(name, author) for name, author in zip(names, authors)]
pprint.pprint(rezult)
