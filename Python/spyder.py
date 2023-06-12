#coding=gbk
import re
import time
import lxml
from urllib.error import URLError, ContentTooShortError, HTTPError
from urllib.parse import urljoin
from lxml.html import tostring, fromstring
import urllib.request
import urllib.request as request
import io
import re
from bs4 import BeautifulSoup
from urllib.error import URLError, HTTPError, ContentTooShortError
from lxml.html import tostring, fromstring
import csv

FIELDS = ('area', 'population', 'iso', 'country_or_district', 'capital', 'continent', 'tld', 'currency_code',
          'currency_name', 'phone', 'postal_code_format', 'postal_code_regex', 'languages', 'neighbours')


class CsvCallback:
    def __init__(self, fields, csvFilePath1,csvFilePath2,csvFilePath3,csvFilePath4):
        self.xpathtotal = 0
        self.csstotal = 0
        self.bs4total = 0
        self.retotal = 0
        
        
        self.fp1 = open(csvFilePath1, 'tw', encoding='utf-8', newline='')
        self.fp2 = open(csvFilePath2, 'tw', encoding='utf-8', newline='')
        self.fp3 = open(csvFilePath3, 'tw', encoding='utf-8', newline='')
        self.fp4 = open(csvFilePath4, 'tw', encoding='utf-8', newline='')
        self.writer1 = csv.writer(self.fp1)     #xpath选择器方法
        self.writer2 = csv.writer(self.fp2)     #re方法
        self.writer3 = csv.writer(self.fp3)     #beautifulsoup方法
        self.writer4 = csv.writer(self.fp4)     #css选择器方法
        self.fields = fields
        self.writer1.writerow(self.fields)
        self.writer2.writerow(self.fields)
        self.writer3.writerow(self.fields)
        self.writer4.writerow(self.fields)
        self.fp1.flush()
        self.fp2.flush()
        self.fp3.flush()
        self.fp4.flush()
        

    def __call__(self, url, html): 
        
        all_row1, all_row2, all_row3, all_row4 = [], [], {}, {}
        if re.search('/view/', url):
            tree = fromstring(html)
            #xpath
            xpathstart = time.perf_counter()
            for field in self.fields:
                selector1 = '//table/tr[@id="places_%s__row"]/td[@class="w2p_fw"]' % field
                td = tree.xpath(selector1)[0]
                all_row1.append(td.text_content()) 
            self.writer1.writerow(all_row1)
            self.fp1.flush()
            xpathend = time.perf_counter()
            xpathtime = xpathend - xpathstart
            self.xpathtotal += xpathtime
            #css
            cssstart = time.perf_counter()
            for field in self.fields:
                selector2 = 'table > tr#places_%s__row > td.w2p_fw' % field
                td = tree.cssselect(selector2)[0]
                all_row2.append(td.text_content()) 
            self.writer2.writerow(all_row2)
            self.fp2.flush()
            cssend = time.perf_counter()
            csstime = cssend - cssstart
            self.csstotal += csstime
            #re
            restart = time.perf_counter()
            for field in self.fields:
                regex = '<tr id="places_%s__row">.*?<td class="w2p_fw">(.*?)</td>' % field
                mo = re.search(regex, html)
                all_row3[field] = mo.group(1)

            all_row3 = list(all_row3)
            self.writer3.writerow(all_row3)
            self.fp3.flush()
            reend = time.perf_counter()
            retime = reend - restart
            self.retotal += retime
            #bs4
            bs4start = time.perf_counter()
            soup = BeautifulSoup(html, features='html.parser')
            table = soup.find(name='table')
            for field in FIELDS:
               tr = table.find(name='tr', attrs={'id': 'places_%s__row' % field})
               td = tr.find(name='td', attrs={'class': 'w2p_fw'})
               all_row4[field] = td.text
            all_row4 = list(all_row4)
            bs4end = time.perf_counter()
            bs4time = bs4end - bs4start
            self.bs4total += bs4time
            self.writer4.writerow(all_row4)
            self.fp4.flush()
        print(f'{self.xpathtotal}s\n{self.csstotal}s\n{self.retotal}s\n{self.bs4total}s')
            
       
             
        

def saveToFile(text: str, filename: str):
    with open(filename, mode='w', encoding='utf-8') as file:
        file.write(text)


def scrape_callback1(url, html):
    if re.search(pattern='/view/', string=url):
        tree = fromstring(html)
        all_row = []
        for field in FIELDS:
            selector = '//table/tr[@id="places_%s__row"]/td[@class="w2p_fw"]' % field
            td = tree.xpath(selector)[0]
            all_row.append(td.text_content())
        print(url, all_row)


def get_links(html):
    webpage_regex = re.compile("""<a[^>]+href=["'](.*?)["']""", re.IGNORECASE)
    links = webpage_regex.findall(html)
    return list(filter(lambda link: len(link.strip()) > 0, links))


def link_crawler(start_url, link_regex, f=None, user_agent='wswp'):
    crawl_queue = [start_url]
    seen = set(crawl_queue)
    while crawl_queue:
        url = crawl_queue.pop()
        html = download(url=url)
        if html is None:
            continue
        if f is not None:
            f(url, html)
        for link in get_links(html):
            if re.match(link_regex, link):
                abs_link = urljoin(start_url, link)
                if abs_link not in seen:
                    seen.add(abs_link)
                    crawl_queue.append(abs_link)


def re_scraper(html):
    results = {}
    for field in FIELDS:
        regex = '<tr id="places_%s__row">.*?<td class="w2p_fw">(.*?)</td>' % field
        mo = re.search(regex, html)
        results[field] = mo.group(1)
    return results


def bs_scraper(html):
    soup = BeautifulSoup(html, features='html.parser')
    table = soup.find(name='table')
    results = {}
    for field in FIELDS:
        tr = table.find(name='tr', attrs={'id': 'places_%s__row' % field})
        td = tr.find(name='td', attrs={'class': 'w2p_fw'})
        results[field] = td.text
    return results


def lxml_scraper(html):
    tree = fromstring(html)
    results = {}
    for field in FIELDS:
        selector = 'table > tr#places_%s__row > td.w2p_fw' % field
        td = tree.cssselect(selector)[0]
        results[field] = td.text_content()
    return results


def lxml_xpath_scraper(html):
    tree = fromstring(html)
    results = {}
    for field in FIELDS:
        selector = '//table/tr[@id="places_%s__row"/td[@class="w2p_fw"]' % field
        td = tree.xpath(selector)[0]
        results[field] = td.text_content()
    return results


def download(url: str, user_agent='wswp', num_retries=2, charset='UTF-8'):
    """Return 网页的HTML代码"""
    print("Downloading:", url)
    response = request.urlopen(url, timeout=30)
    time.sleep(1)
    textIOWrapper = io.TextIOWrapper(buffer=response, encoding='utf-8')
    html = textIOWrapper.read()
    return html




url = 'http://180.201.165.235:8000/places'
regex = '/places/default/(index|view)/'
csvFilePath1 = r'C:\Users\Scott\Desktop\yes1.csv'
csvFilePath2 = r'C:\Users\Scott\Desktop\yes2.csv'
csvFilePath3 = r'C:\Users\Scott\Desktop\yes3.csv'
csvFilePath4 = r'C:\Users\Scott\Desktop\yes4.csv'
csvCallback = CsvCallback(FIELDS, csvFilePath1,csvFilePath2,csvFilePath3,csvFilePath4)
link_crawler(url, regex, f=csvCallback, user_agent='abc')

