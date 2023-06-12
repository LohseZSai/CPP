from zipfile import ZipFile
from io import BytesIO, TextIOWrapper
import csv, pprint, requests


class AlexaCallback:
    def __init__(self, max_urls=100):
        self.max_urls = max_urls
        self.filePath = r"C:\Users\Scott\Documents\Tencent Files\1172720089\FileRecv/top-1m.csv.zip"
        self.urls = []

    def __call__(self):
        with ZipFile(self.filePath) as zf:
            csv_filename = zf.namelist()[0]
            with zf.open(csv_filename) as csv_file:
                for number, website in csv.reader(TextIOWrapper(csv_file)):
                    self.urls.append('http://' + website)
                    if len(self.urls) == self.max_urls:
                        break
        return self.urls


if __name__ == '__main__':
    alexa = AlexaCallback(max_urls=100)
    alexa()
    pprint.pprint(alexa.urls)
