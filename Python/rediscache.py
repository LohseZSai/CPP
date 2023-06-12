import json
from redis import StrictRedis
from datetime import timedelta
import zlib


class RedisCache:
    def __init__(self, client=None, expires=timedelta(days=30), encoding='utf-8', compress=True):
        if client is None:
            self.client = StrictRedis(host='localhost', port=6379, password='Litj', db=0)
        else:
            self.client = client
        self.expires = expires
        self.encoding = encoding
        self.compress = compress

    def close(self):
        if self.client is not None:
            self.client.close()

    def __getitem__(self, url):
        record = self.client.get(url)
        if record:
            if self.compress:
                record = zlib.decompress(record)
            return json.loads(record.decode(self.encoding))
        else:
            raise KeyError(url + 'does not exist')

    def __setitem__(self, url, result):
        data = json.dumps(result)
        data = bytes(data, self.encoding)
        if self.compress:
            data = zlib.compress(data)
        self.client.setex(url, self.expires, data)
