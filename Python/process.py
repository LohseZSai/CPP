import multiprocessing
import os
import re
import socket
import threading
import time
from another import get_links
from urllib.parse import urljoin, urlsplit
from redis import StrictRedis
from allexcallback import AlexaCallback
from Downloader import Downloader


class RedisQueue:
    def __init__(self, host='localhost', port=6379,
                 password='Litj', db=0, queue_name='wswp'):
        self.client = StrictRedis(host=host, port=port, password=password, db=db)
        self.name = "queue:%s" % queue_name
        self.seen_set = "seen:%s" % queue_name

    def close(self):
        if self.client is not None:
            self.client.close()

    def __len__(self):
        return self.client.llen(self.name)

    def clear(self):
        self.client.delete(*[self.name, self.seen_set])

    def push(self, element):
        if isinstance(element, list):
            element = [e for e in element if not self.already_seen(e)]
            if len(element):
                self.client.lpush(self.name, *element)
                self.client.sadd(self.seen_set, *element)
        elif not self.already_seen(element):
            self.client.lpush(self.name, element)
            self.client.sadd(self.seen_set, element)

    def pop(self):
        return self.client.rpop(self.name).decode(encoding='UTF-8')

    def already_seen(self, element):
        return self.client.sismember(self.seen_set, element)


def threaded_crawler_rq(link_regex, scrape_callback=None, delay=5, user_agent='wswp',
                        proxies=None, cache={}, num_retries=2, max_threads=5, host='localhost',
                        port=6379, password='Litj', db=0, queue_name='wswp'):
    crawl_RQ = RedisQueue(host=host, port=port, password=password, db=db, queue_name=queue_name)
    rp_dict = dict()
    D = Downloader(delay=delay, user_agent=user_agent, proxies=proxies, cache=cache)
    print(f'我是子进程 ID={os.getpid()},父进程 ID={os.getpid()}')

    def process_queue():
        while len(crawl_RQ):
            print(f'{threading.current_thread().getName()} of 子进程(ID={os.getpid()}')
            url = crawl_RQ.pop()
            components = urlsplit(url)
            start_url = 'http://' + components.netloc
            if start_url not in rp_dict.keys():
                rp_dict[start_url] = None
            rp = rp_dict[start_url]
            no_robots = (rp is None)
            if (not no_robots) and (not rp.can_fetch(user_agent, url)):
                print(f'Skipping:{url}')
                continue
            html = D(url, num_retries=num_retries)
            if html is None:
                continue
            if scrape_callback is not None:
                scrape_callback(url, html)
            for link in get_links(html):
                if re.match(link_regex, link):
                    abs_link = urljoin(start_url, link)
                    crawl_RQ.push(abs_link)

    threads = []
    while len(threads) < max_threads and crawl_RQ:
        thread = threading.Thread(target=process_queue)
        print('开启一个新线程：', thread.getName())
        thread.setDaemon(True)
        thread.start()
        threads.append(thread)
    for thread in threads:
        thread.join()
        print(f'{thread.getName()}:{thread.is_alive()}')
    crawl_RQ.close()
    print(f'子进程(ID={os.getpid()})结束')


def mp_threaded_crawler(start_urls, **kwargs):
    RQ = RedisQueue(host=kwargs.get('host'), port=kwargs.get('port'), password=kwargs.get('password'),
                    db=kwargs.get('db'), queue_name=kwargs.get('queue_name'))
    RQ.clear()
    RQ.push(start_urls)
    RQ.close()
    num_procs = kwargs.pop('num_procs')
    if not num_procs:
        num_procs = multiprocessing.cpu_count()
    processes = []
    for i in range(num_procs):
        proc = multiprocessing.Process(target=threaded_crawler_rq, kwargs=kwargs)
        proc.start()
        processes.append(proc)
    for proc in processes:
        proc.join()

if __name__=='__main__':
    print(f'我是主进程 ID={os.getpid()}')
    timeout=10
    socket.setdefaulttimeout(timeout)
    alexa = AlexaCallback(max_urls=500)
    start_urls = alexa()
    print(start_urls)
    host='localhost'
    port=6379
    password='Litj'
    db=0
    queue_name='wswp'
    link_regex = '$^'
    kwargs={'link_regex':link_regex,'num_procs':2,'max_threads':4,
            'host':host,'port':port,'password':'Litj','db':db,
            'queue_name':queue_name}
    start = time.time()
    mp_threaded_crawler(start_urls,**kwargs)
    end = time.time()
    seconds = end - start
    hours = int(seconds / 3600)
    mins = int(seconds % 3600 // 60)
    secs = seconds % 60
    print("Wall time:%d hours %d mins %f secs" % (hours, mins, secs))



