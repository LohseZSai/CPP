#coding=gbk
from bs4 import BeautifulSoup
from lxml.html import fromstring
import time
import urllib.request as request
import io
import re


FIELDS = ('area', 'population', 'iso', 'country_or_district', 'capital', 'continent', 'tld', 'currency_code',
          'currency_name', 'phone', 'postal_code_format', 'postal_code_regex', 'languages', 'neighbours')


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
        selector = '//table/tr[@id="places_%s__row"]/td[@class="w2p_fw"]' % field
        td = tree.xpath(selector)[0]
        results[field] = td.text_content()
    return results


def download(url: str, user_agent='wswp', num_retries=2, charset='utf-8'):
    response = request.urlopen(url, timeout=30)
    textIOWrapper = io.TextIOWrapper(buffer=response, encoding='utf-8')
    html = textIOWrapper.read()
    return html


NUM_ITERATIONS = 1000
url = 'http://180.201.165.235:8000/places/default/view/Unnited-Kingdom233'
html = download(url)
scrapers = [('Regular expressions', re_scraper),
            ('BeautifulSoup', bs_scraper),
            ('Lxml', lxml_scraper),
            ('XPath', lxml_xpath_scraper)]
for name, scraper in scrapers:
    start = time.time()
    for i in range(NUM_ITERATIONS):
        if scraper == re_scraper:
            re.purge()
        result = scraper(html)
        assert result['area'] == '244820 square kilometres', '数据错误！'
    end = time.time()
    print('%s:%.2f seconds' % (name, end - start))
