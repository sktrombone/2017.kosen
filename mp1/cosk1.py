import requests
from requests.auth import HTTPDigestAuth
set = requests.Session()
url = 'http://kosaka004.je.tokyo-ct.ac.jp/studentreports/3Jucom.php?'
r = set.get(url, auth=HTTPDigestAuth('s15097', 's15097'))
files = {'fileselect':('mp5ex01.txt', open('mp5ex01.txt','rb'),'text/plain')}
res = set.post(url,files=files)
print (res.text)
print (res.status_code , '\n' , res.headers)
f = open("cosk1.html","w")
f.write(res.text)
