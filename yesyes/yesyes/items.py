# Define here the models for your scraped items
#
# See documentation in:
# https://docs.scrapy.org/en/latest/topics/items.html

import scrapy


class YesyesItem(scrapy.Item):
    name = scrapy.Field()
    money = scrapy.Field()
       # define the fields for your item here like:
    # name = scrapy.Field()