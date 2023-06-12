from selenium.webdriver.common.by import By
from selenium import webdriver
import time
from docx import Document
from selenium.common.exceptions import NoSuchElementException
from selenium.webdriver.edge.options import Options
from concurrent.futures import ThreadPoolExecutor

def cratchurls():
    driver.get('https://newssearch.chinadaily.com.cn/en/search?cond=%7B%22titleMust%22%3A%22energy%22%2C%22fullMust%22%3A%22energy%22%2C%22sort%22%3A%22dp%22%2C%22duplication%22%3A%22on%22%7D&language=en')
    time.sleep(2)
    driver.maximize_window()
    count = 1
    for j in range(520):
        for i in range(1, 11):
            button = driver.find_element(By.XPATH, f'/html/body/div[5]/div[2]/div[5]/div[3]/div[{i}]/span/h4/a')
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

def scrape(link):
    driver = webdriver.Edge()
    driver.implicitly_wait(30)
    try:
        driver.get(link)
        time.sleep(2)
        try:
            txt = driver.find_element(By.XPATH, '//*[@id="Content"]').text
        except NoSuchElementException:
            try:
                txt = driver.find_element(By.XPATH, '//*[@class="artTxt"]').text
            except NoSuchElementException:
                txt = ""  # 如果无法定位到日期元素，将txt设置为空字符串或其他默认值
        return txt
    finally:
        driver.quit()

if __name__ == "__main__":
    options = Options()
    options.add_argument('headless')
    options.add_experimental_option('excludeSwitches', ['enable-logging'])
    driver = webdriver.Edge(options=options)
    titles, words, dates = [], [], []
    links = []
    cratchurls()

    with ThreadPoolExecutor(max_workers=8) as executor:
        results = executor.map(scrape, links)

    words.extend(results)
    driver.quit()

  