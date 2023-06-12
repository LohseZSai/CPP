import sys
from Downloader import Downloader
import re, time, requests, socket
from urllib.parse import urljoin, urlsplit
from urllib import robotparser
from allexcallback import AlexaCallback


def saveToFile(text: str, filename: str):
    with open(filename, mode='w', encoding='utf-8') as file:
        file.write(text)


def get_robots_parse(robots_url):
    try:
        rp = robotparser.RobotFileParser()
        rp.set_url(robots_url)
        rp.read()
        return rp
    except(UnicodeDecodeError, Exception) as e:
        return None


def get_links(html):
    webpage_regex = re.compile("""<a[^>]+href=["'](.*?)["']""", re.IGNORECASE)
    links = webpage_regex.findall(html)
    return list(filter(lambda link: len(link.strip()) > 0, links))


def link_crawler(start_urls, link_regex, scrape_callback=None, delay=1, user_agent='wswp', proxies=None, cache={},
                 num_retries=1):
    crawl_queue = start_urls.copy()
    seen = set(crawl_queue)
    rp_dict = dict()
    for start_url in start_urls:
        rp = get_robots_parse(f'{start_url}/robots.txt')
        rp_dict[start_url] = rp
    D = Downloader(delay=delay, user_agent=user_agent, proxies=proxies, cache=cache)
    while crawl_queue:
        url = crawl_queue.pop()
        start_url = 'http://' + urlsplit(url).netloc
        rp = rp_dict[start_url]
        if (rp is not None) and (not rp.can_fetch(user_agent, url)):
            print(f'Skipping:{url}')
            continue
        html = D(url, num_retries=num_retries)
        if html is None:
            continue
        if scrape_callback is None:
            continue
        scrape_callback(url, html)
        for link in get_links(html):
            if re.match(link_regex, link):
                abs_link = urljoin(start_url, link)
                if abs_link not in seen:
                    seen.add(abs_link)
                    crawl_queue.append(abs_link)

if __name__ == '__main__':
    timeout = 1
    socket.setdefaulttimeout(timeout)
    alexa = AlexaCallback(max_urls=100)
    start_urls = alexa()
    regex = '$^'
    start = time.time()
    link_crawler(start_urls, regex, scrape_callback=None, cache={})
    end = time.time()
    seconds = end - start
    hours = int(seconds / 3600)
    mins = int(seconds % 3600 // 60)
    secs = seconds % 60
    print("Wall time:%d hours %d mins %f secs" % (hours, mins, secs))
