#coding=utf-8
from zipfile import ZipFile
from io import BytesIO,TextIOWrapper
from urllib.parse import *
import requests,csv,pprint
import re,socket
import random
import time
from urllib.parse import urljoin,urlsplit
from urllib import robotparser
class AlexaCallback:
    def __init__(self, max_urls=500):
        self.max_urls = max_urls
        self.filepath= r'C:\Users\Scott\Documents\Tencent Files\1172720089\FileRecv/top-1m.csv.zip'
        self.urls = []
    def __call__(self):
        with ZipFile(self.filepath) as zf:
            csv_filename = zf.namelist()[0]
            with zf.open(csv_filename) as csv_file:
                for _, website in csv.reader(TextIOWrapper(csv_file)):
                    self.urls.append('http://' + website)
                    if len(self.urls) == self.max_urls:
                        break
        return self.urls
# if __name__ == '__main__':
#     alexa = AlexaCallback(max_urls=100)
#     alexa() # alexa.__call__()
#     pprint.pprint(alexa.urls)
# from zipfile import ZipFile
# from io import TextIOWrapper
# import csv, pprint
# class AlexaCallback:
# def __init__(self, max_urls=500):
# self.max_urls = max_urls
# self.filePath = 'd:/top-1m.csv.zip'
# self.urls = []
# def __call__(self):
# with ZipFile(self.filePath) as zf:
# csv_filename = zf.namelist()[0]
# with zf.open(csv_filename) as csv_file:
# for _, website in csv.reader(TextIOWrapper(csv_file)):
# self.urls.append('http://' + website)
# if len(self.urls) == self.max_urls:
# break
# return self.urls
# if __name__ == '__main__':
# alexa = AlexaCallback(max_urls=10)
# alexa() # alexa.__call__()
# pprint.pprint(alexa.urls)
class Downloader:
    def __init__(self, delay=5, user_agent='wswp', proxies=None, cache={}):
        self.throttle = Throttle(delay)
        self.user_agent = user_agent
        self.proxies = proxies
        self.num_retries = None  # we will set this per request
        self.cache = cache

    def __call__(self, url, num_retries=2):
        self.num_retries = num_retries
        try:
            result = self.cache[url]
            print('Loaded from cache:', url)
        except KeyError:
            result = None
        if result and 500 <= result['code'] <= 600 and self.num_retries:
            result = None
        if result is None:
            self.throttle.wait(url)
            proxies = random.choice(self.proxies) if self.proxies else None
            headers = {'User-Agent': self.user_agent}
            result = self.download(url, headers, proxies)
            if self.cache:
                self.cache[url] = result
        return result['html']

    def download(self, url: str, headers, proxies):
        print('Downloading:', url)
        response = None
        try:
            response = requests.get(url=url, headers=headers, proxies=proxies, timeout=10)
            response.encoding = response.apparent_encoding
            html = response.text
            if response.status_code != 200:
                print('Error code:', response.status_code)
                html = None
                if self.num_retries > 0 and response.status_code >= 400:
                    delay = 5  # 延迟发送请求的秒数
                    print(f'Pause for {delay} seconds.')
                    time.sleep(delay)  # 暂停执行若干秒
                    print('Retry to download.')
                    self.num_retries -= 1
                    return self.download(url, headers=headers, proxies=proxies)  # 重试下载
            else:
                print('encoding=', response.encoding)
            code = response.status_code
        except Exception as e:
            print('Download error:', e)
            if hasattr(e, 'code'):
                print('Error code:', e.code)
            html = None
            code = 404 if response is None else response.status_code
        return {'html': html, 'code': code}
class Throttle:  # 节流阀 记录每个域名上次访问的时间
    """Add a delay between downloads to the same domain"""

    def __init__(self, delay):
        self.delay = delay
        self.domains = {}

    def wait(self, url):
        domain = urlparse(url).netloc
        last_accessed = self.domains.get(domain)
        if self.delay > 0 and last_accessed is not None:
            sleep_seconds = self.delay - (time.time() - last_accessed)
            if sleep_seconds > 0:
                time.sleep(sleep_seconds)
        self.domains[domain] = time.time()

def get_robots_parse(robots_url):
    try:
        rp = robotparser.RobotFileParser() # 创建对象
        rp.set_url(robots_url)
        rp.read()
        return rp
    except (UnicodeDecodeError, Exception) as e:
        return None
def link_crawler(start_urls, link_regex, scrape_callback=None, delay=5, user_agent='wswp', proxies=None, cache={},
                 num_retries=2):
    crawl_queue = start_urls.copy()  # 注意如果直接crawl_queue = start_urls，则两个引用的是同一列表
    seen = set(crawl_queue)  # 根据列表创建一个新集合
    rp_dict = dict()  # 该字典用来存储每个域名的解析器
    for start_url in start_urls:
        rp = get_robots_parse(f'{start_url}/robots.txt')
        rp_dict[start_url] = rp
    D = Downloader(delay=delay, user_agent=user_agent, proxies=proxies, cache=cache)
    while crawl_queue:
        url = crawl_queue.pop()  # 弹出队列首元素（链接）
        start_url = 'http://' + urlsplit(url).netloc
        rp = rp_dict[start_url]  # 取出url所在网站的域名所对应的rp(即robots解析器)
        no_robots = (rp is None)  # 是否存在robots.txt
        # 如果存在robots.txt文件且其中禁止访问该url，则跳过下载
        if (not no_robots) and (not rp.can_fetch(user_agent, url)):
            print(f'Skipping: {url}')
            continue
        html = D(url, num_retries=num_retries)
        if html is None:
            continue
        if scrape_callback is None:
            continue
        scrape_callback(url, html)
        # filter for links matching our regular expression
        for link in get_links(html):
            if re.match(link_regex, link):
                abs_link = urljoin(start_url, link)
                # check if have already seen this link
                if abs_link not in seen:
                    seen.add(abs_link)
                    crawl_queue.append(abs_link)  # 绝对链接加入队列末尾
if __name__ == '__main__':
    timeout = 10
    socket.setdefaulttimeout(timeout)
    alexa = AlexaCallback(max_urls=10)
    start_urls = alexa()
    regex = '$^'  # 使用'$^'作为模式，避免收集每个页面的链接。
    start = time.time()
    link_crawler(start_urls, regex, scrape_callback=None, cache={})
    end = time.time()
    seconds = end - start
    hours = int(seconds / 3600)
    mins = int(seconds % 3600 // 60)
    secs = seconds % 60
    print("Wall time: %d hours %d mins %f secs" % (hours, mins, secs))


