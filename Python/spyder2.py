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
    def __init__(self,fields,csvFilePath):
        self.fp = open(csvFilePath,'tw',encoding='utf-8',newline='')
        self.writer = csv.writer(self.fp)
        self.fields = fields
        self.writer.writerow(self.fields)
        self.fp.flush()
        
        
        
        
    def __call__(self,url,html):
        if re.search('/view/',url):
            tree = fromstring(html)
            all_row = []
            for field in self.fields:
                print(6)
                selector = '//table/tr[@id="places_%s__row"]/td[@class="w2p_fw"]' %field
                td = tree.xpath(selector)[0]
                all_row.append(td.text_content())
            print(all_row)    
            self.writer.writerow(all_row)
            
            
    
                

def saveToFile(text: str, filename: str):
    with open(filename, mode='w', encoding='utf-8') as file:
        file.write(text)

def scrape_callback1(url,html):
    if re.search(pattern='/view/', string=url):
        tree = fromstring(html)
        all_row = []
        for field in FIELDS:
            selector = '//table/tr[@id="places_%s__row"]/td[@class="w2p_fw"]' %field
            td = tree.xpath(selector)[0]
            all_row.append(td.text_content())
        print(url,all_row)
            
def get_links(html):
    
    webpage_regex = re.compile("""<a[^>]+href=["'](.*?)["']""", re.IGNORECASE)
    links = webpage_regex.findall(html)
    return list(filter(lambda link: len(link.strip()) > 0, links))


            
def link_crawler(start_url, link_regex,user_agent='wswp',scrape_callback=None):
    crawl_queue = [start_url]
    seen = set(crawl_queue)
    while crawl_queue:
        url = crawl_queue.pop()  
        html = download(url=url)
        if html is None:
            continue
        if scrape_callback is not None:
            scrape_callback1(url,html)
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
csvFilePath = r'C:\Users\Scott\Desktop\yesyes.csv'
csvCallback = CsvCallback(FIELDS, csvFilePath)
link_crawler(url, regex,scrape_callback1)

