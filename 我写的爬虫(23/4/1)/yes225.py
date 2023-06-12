from selenium.webdriver.common.by import By
from selenium import webdriver
import pprint
import time
import pandas as pd
import jieba
from docx import Document
from selenium.common.exceptions import NoSuchElementException
from selenium.webdriver.edge.options import Options
import threading

def cratchurls(start_index, end_index):
    global count
    driver.get('https://newssearch.chinadaily.com.cn/en/search?cond=%7B%22titleMust%22%3A%22energy%22%2C%22fullMust%22%3A%22energy%22%2C%22sort%22%3A%22dp%22%2C%22duplication%22%3A%22on%22%7D&language=en')
    for j in range(start_index, end_index):
        for i in range(1, 11):
            button =  driver.find_element(By.XPATH, f'/html/body/div[5]/div[2]/div[5]/div[3]/div[{i}]/span/h4/a')  
            link = button.get_attribute("href")
            links.append(link)
            title = button.text
            date = driver.find_element(By.XPATH, f'/html/body/div[5]/div[2]/div[5]/div[3]/div[{i}]/span/b[1]').text
            dates.append(date)
            titles.append(title)
            time.sleep(0.5)
            with open(r'C:\Users\Scott\CPP\我写的爬虫(23\4\1)\data2.txt', 'a') as file:
                file.write(link + '\n')
            with open(r'C:\Users\Scott\CPP\我写的爬虫(23\4\1)\title.txt', 'a', errors='ignore') as file:
                file.write(title + '\n')
            with open(r'C:\Users\Scott\CPP\我写的爬虫(23\4\1)\date.txt', 'a') as file:
                file.write(date + '\n')
            print(f"finish {count} of 5200")
            count += 1

        if j == 0:
            nextbutton = driver.find_element(By.XPATH, '/html/body/div[5]/div[2]/div[5]/div[1]/div[2]/span/a[5]')
            driver.execute_script("arguments[0].click();", nextbutton)         
        else:
            nextbutton1 = driver.find_element(By.XPATH, '/html/body/div[5]/div[2]/div[5]/div[1]/div[2]/span/a[6]')
            driver.execute_script("arguments[0].click();", nextbutton1)

def run_threaded_crawler():
    threads = []
    total_pages = 520
    threads_per_page = 8
    pages_per_thread = total_pages // threads_per_page
    remaining_pages = total_pages % threads_per_page

    for i in range(threads_per_page):
        start_index = i * pages_per_thread + 1
        end_index = start_index + pages_per_thread
        if i == threads_per_page - 1:
            end_index += remaining_pages
        t = threading.Thread(target=cratchurls, args=(start_index, end_index))
        threads.append(t)
        t.start()

    for thread in threads:
        thread.join()


if __name__ == "__main__":
    options = Options()
    options.add_argument('--headless=new')
    options.add_experimental_option('excludeSwitches', ['enable-logging'])
    driver = webdriver.Edge()
    titles, words, dates = [], [], []
    links = []
    count = 1

    run_threaded_crawler()

    driver.close()