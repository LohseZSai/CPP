from diskcache import DiskCache
from rediscache import RedisCache
import time
from yunxing import link_crawler, scrape_callback
 
 
url = 'http://180.201.165.235:8000/places/'
regex = '/places/default/(index|view)/'
start = time.time()
link_crawler(url, regex, scrape_callback=scrape_callback, cache=RedisCache())
end = time.time()
seconds = end - start
hours = int(seconds / 3600)
mins = int(seconds % 3600 // 60)
secs = seconds % 60
print("Wall time:%d hours %d mins %f secs" % (hours, mins, secs))