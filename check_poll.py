import requests
from bs4 import BeautifulSoup
from collections import namedtuple
# import selenium

url = 'http://localhost:8080'

headers = {
	'User-Agent': 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:126.0) Gecko/20100101 Firefox/126.0'
}

header_complete = {
    'User-Agent': 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:126.0) Gecko/20100101 Firefox/126.0',
    'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8',
    'Accept-Language': 'en-US,en;q=0.5',
    'Accept-Encoding': 'gzip, deflate, br',
    'Connection': 'keep-alive',
    'Upgrade-Insecure-Requests': '1'
}
# print(requests.get(url, headers=headers).text)
#sends request to url using headers
# for i in range(0, 5):
# 	requests.get(url, headers=header_complete)
response = requests.get(url, headers=header_complete)
a = requests.get(url, headers=headers)
# b = requests.get(url, headers=header_complete)
# c = requests.get(url, headers=header_complete)
print(response.content)
print(a.text)
# print(b.text)
# print(c.text)

# if (response.status_code == 200):