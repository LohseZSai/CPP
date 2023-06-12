from yunxing import link_crawler,scrape_callback
from rediscache import RedisCache,StrictRedis
import time
url = 'http://180.201.165.235:8000/places/'
regex = '/places/default/(index|view)/'
redis_cli=StrictRedis(host='localhost', port=6379, password='Litj', db=0)
redisCash=RedisCache(client=redis_cli)
start=time.time()
link_crawler(url,regex,scrape_callback=scrape_callback,cache=redisCash)
end=time.time()
seconds=end-start
hours=int(seconds / 3600)
mins=int(seconds % 3600 // 60)
secs=seconds % 60
print("Wall time:%d hours %d mins %f secs" % (hours, mins, secs))
redisCash.close()


