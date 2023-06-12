from scrapy import cmdline

cmd = "scrapy crawl yesyesa -s LOG_LEVEL=ERROR"
cmdline.execute(cmd.split())