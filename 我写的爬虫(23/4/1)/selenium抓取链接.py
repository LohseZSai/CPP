from selenium.webdriver.common.by import By
from selenium import webdriver
import pprint
import time
import pandas as pd
import jieba
from docx import Document
from selenium.common.exceptions import NoSuchElementException
from selenium.webdriver.edge.options import Options
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC

def cratchurls():
    driver.get('https://newssearch.chinadaily.com.cn/en/search?cond=%7B%22titleMust%22%3A%22energy%22%2C%22fullMust%22%3A%22energy%22%2C%22sort%22%3A%22dp%22%2C%22duplication%22%3A%22on%22%7D&language=en')
    time.sleep(2)
    driver.maximize_window()
    count = 1
    for j in range(520):
        for i in range(1, 11):
            #窗口等待，不加载出来就不抓取
            time.sleep(0.5)
            button_locator = (By.XPATH, f'/html/body/div[5]/div[2]/div[5]/div[3]/div[{i}]/span/h4/a')
            WebDriverWait(driver, 10).until(EC.visibility_of_element_located(button_locator))
            button = driver.find_element(*button_locator)
            link = button.get_attribute("href")
            links.append(link)
            title = button.text
            date_locator = (By.XPATH, f'/html/body/div[5]/div[2]/div[5]/div[3]/div[{i}]/span/b[1]')
            WebDriverWait(driver, 10).until(EC.visibility_of_element_located(date_locator))
            date = driver.find_element(*date_locator).text
            dates.append(date)
            titles.append(title)
            
            with open(r'C:\Users\Scott\CPP\我写的爬虫(23\4\1)\data2.txt', 'a') as file:  # 'a' 表示以追加模式打开文件，如果文件不存在则创建新文件
                file.write(link + '\n')
            with open(r'C:\Users\Scott\CPP\我写的爬虫(23\4\1)\title.txt', 'a', errors='ignore') as file:
                file.write(title + '\n')
            with open(r'C:\Users\Scott\CPP\我写的爬虫(23\4\1)\date.txt', 'a') as file:  # 'a' 表示以追加模式打开文件，如果文件不存在则创建新文件
                file.write(date + '\n')
            print(f"finish {count} of 5200")
            count += 1
        if j == 0:
            nextbutton = driver.find_element(By.XPATH,'/html/body/div[5]/div[2]/div[5]/div[1]/div[2]/span/a[5]')
            driver.execute_script("arguments[0].click();", nextbutton)         
        else:
            nextbutton1 = driver.find_element(By.XPATH,'/html/body/div[5]/div[2]/div[5]/div[1]/div[2]/span/a[6]')
            driver.execute_script("arguments[0].click();", nextbutton1)  




        
        
        
if __name__ == "__main__":
    # 使用selenium完整的完成以前单纯使用爬取一个步骤完成的任务
    options = Options()
    options.add_argument('--headless=new')
    options.add_experimental_option('excludeSwitches', ['enable-logging'])
    driver = webdriver.Edge()
    titles,dates = [],[]
    #进入网站
    links = []
    cratchurls()
    
    driver.close()

    