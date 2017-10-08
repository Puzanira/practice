import urllib.request
import re
import requests

j = open('output.txt', 'w', encoding = 'utf-8')
with open('sourses.txt', 'r', encoding = 'utf-8') as f:
    text = f.readlines()
    for line in text:
        line = re.sub('\n', '', line)
        line = re.sub('\ufeff', '', line)
        
        page = urllib.request.urlopen(line)
        r = requests.get(line)
        charset = r.encoding
        print(charset)
        pageinfo = page.read().decode(charset)
        
        title1 = re.compile('<title>.*?</title>')
        title = title1.findall(pageinfo)
        meta1 = re.compile('<meta.*?>')
        meta = meta1.findall(pageinfo)
        with open('output.txt', 'a', encoding = 'utf-8') as f:
            f.write('По ссылке: ' + line + '\n' + 'В заголовке: ')
            for t in title:
                t = re.sub('<.*?>', '', t)
                f.write(t + '\n')
            f.write('В метаданных: \n')
            for m in meta:
                f.write(m + '\n')
            f.write('\n\n')
j.close()        
