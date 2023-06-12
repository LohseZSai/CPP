import re

def extract_date_from_url(url):
    # 提取日期信息的正则表达式模式
    pattern = r'(\d{4}).*?(\d{2}).*?(\d{2})'
    
    # 在URL中查找日期信息
    match = re.search(pattern, url)
    if match:
        year = match.group(1)
        month = match.group(2)
        day = match.group(3)
        return f"{year}{month}{day}"
    else:
        return None

# 示例使用
url = "http://www.chinadaily.com.cn/en/cd/2002-11/19/content_144333.htm"
date = extract_date_from_url(url)
print(date)  # 输出：20020114
