from selenium import webdriver
driver = webdriver.Edge(executable_path='C:/edgedriver_win64/msedgedriver.exe')
driver.get('http://180.201.165.235:8000/places/default/search')
driver.find_element(by=By.ID, value='search_term').send_keys('.')
js = "document.getElementByld('page_size').options[1].text='1000';"
driver.execute_script(js)
driver.find_element(by=By.ID,value='search').click()
driver.implicitly_wait(30)
links = driver.find_elements(by=By.CSS_SELECTOR,value='#results a')
countries_or_districts = [link.text for link in links]
print(countries_or_districts)
driver.close()
