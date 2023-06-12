import os,re,json
from urllib.parse import urlsplit
from yunxing import link_crawler,scrape_callback
import time

class DiskCache:
    def __init__(self,cache_dir='D:/cache',max_len=255):
        self.cache_dir=cache_dir
        self.max_len=max_len

    def url_to_path(self,url):
        components=urlsplit(url)
        path=components.path
        if not path:
            path='/index.html'
        elif path.endswith('/'):
            path+='index.html'
        filename=components.netloc+path+components.query
        filename=re.sub(pattern='[^-/0-9a-zA-Z~.:__{}!@#%&+]',repl='__',string=filename)
        filename='/'.join(segment[:self.max_len] for segment in filename.split('/'))
        return os.path.join(self.cache_dir,filename)

    def __getitem__(self, url):
        path=self.url_to_path(url)
        if os.path.exists(path):
            with open(path,'tr') as fp:
                return json.load(fp)
        else:
            raise KeyError(url+'does not exist')

    def __setitem__(self, url, result):
        path=self.url_to_path(url)
        folder=os.path.exists(path)
        if not os.path.exists(folder):
            os.makedirs(folder)
        with open(path,'tw')as fp:
            json.dump(result,fp)

if __name__=='__main__':
    url='http://180.201.165.235:8000/places//'
    regex='/places/default/(index|view)/'
    start=time.time()
    link_crawler(url,regex,scrape_callback=scrape_callback,cache=DiskCache())
    end=time.time()

    seconds=end-start
    hours=int(seconds/3600)
    mins=int(seconds%3600//60)
    secs=seconds%60
    print('Wall time:%d hours %d mins %f secs'%(hours,mins,secs))
