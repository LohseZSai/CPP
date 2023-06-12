import requests
import pprint
import string
import time

PAGE_SIZE = 10

template_url = 'http://180.201.165.235:8000/places/ajax/search.json?&search_term={}&page_size={}&page={}'
countries_or_districts = set()

for letter in string.ascii_uppercase:
    print(f'Searching with{letter}')
    page = 0
    while True:
        url = template_url.format(letter, PAGE_SIZE, page)
        resp = requests.get(url)
        resp.encoding = resp.apparent_encoding
        data = resp.json()
        time.sleep(1)
        records_num = len(data.get('records'))
        print(f'adding{records_num} more records from page {page}')
        for record in data.get("records"):
            countries_or_districts.add(record['country_or_district'])
        page += 1
        if page > data.get('num_pages'):
            break

pprint.pprint(countries_or_districts)

with open('D:/countries_or_districts.txt','tw')as file:
    file.write('\n'.join(sorted(countries_or_districts)))