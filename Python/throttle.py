import time
from urllib.parse import*
class Throttle:
    def __init__(self,delay):
        self.delay=delay
        self.domains={}
    def wait(self,url):
        domain=urlparse(url).netloc
        last_accessed=self.domains.get(domain)
        if self.delay>0 and last_accessed is not None:
            sleep_secs=self.delay-(time.time()-last_accessed)
            if sleep_secs>0:
                time.sleep(sleep_secs)
        self.domains[domain]=time.time()