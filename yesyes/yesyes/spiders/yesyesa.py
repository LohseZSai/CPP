import scrapy
from scrapy.linkextractors import LinkExtractor
from scrapy.spiders import CrawlSpider, Rule
from yesyes.items import YesyesItem
from scrapy import Selector

class YesyesaSpider(CrawlSpider):
   name = 'yesyesa'
   cities = ['bj','sh','cs']
   allowed_domains = ['bj.fang.ke.com']
   start_urls = ['https://bj.fang.ke.com/loupan/']

#    rules = (
#         Rule(LinkExtractor(allow=r'/index/', deny=r'/user/'), follow=True),
#         Rule(LinkExtractor(allow=r'/view/', deny=r'/user/'), callback='parse'),
#     )
   
   def parse(self, response):#最重要的部分，爬取结构！内容
         #管道接收字典
        sel = Selector(response)
        list_items = sel.xpath('//*[@class="resblock-list post_ulog_exposure_scroll has-results"]')
        for list_item in list_items:
          item = YesyesItem()
          item['money'] = list_item.xpath('./div[1]/span[1]/text()').extract()
          item['name'] = list_item.xpath('./li[3]/div/div[1]/a/text()').extract()
          yield YesyesItem