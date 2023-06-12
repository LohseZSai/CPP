import pprint
import pandas as pd

with open(r'C:\Users\Scott\CPP\我写的爬虫(23\4\1)\data2.txt', 'r') as file:
    links = ([line.strip() for line in file.readlines()])[:1000]
    urls = [(i, link) for i, link in zip(range(len(links)), links)]
    df = pd.DataFrame(urls, columns=['i', 'urls'])

words = []
for link in links:
    result = df[df['urls'] == link]['i'].index
    words.append((result[0],link))
    
    
pprint.pprint(words)