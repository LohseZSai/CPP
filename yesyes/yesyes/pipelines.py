# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://docs.scrapy.org/en/latest/topics/item-pipeline.html


# useful for handling different item types with a single interface
from itemadapter import ItemAdapter
from csv import DictWriter
from yesyes.items import YesyesItem 

class YesyesPipeline:
    def open_spider(self,spider):
        filename = 'yesyes.csv'
        spider.logger.info(f'启动！！开始写入{filename}')
        self.file = open(filename,'wt',newline='')
        self.dictWriter = DictWriter(self.file,fieldnames=YesyesItem.fields.keys())
        self.dictWriter.writeheader()

    def process_item(self, item, spider):
        spider.logger.info(f'保存记录！！开始保存{self.file.name}')
        self.dictWriter.writerow(item)
        self.file.flush()
        return item
    def close_spider(self,spider):
        spider.logger.info(f'文件{self.file.name}完成啦！')
        self.file.close()

