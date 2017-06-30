
# -*- coding: utf-8 -*-

'说明： '  

import sys, os
import requests

url = 'http://123.57.79.160/handle'

files = {'Filename': 'test.wav',

        'Filedata':( 'test.wav',open(u'test.wav','rb'), 'application/octet-stream' ),

        'Upload': 'Submit Query'
}

#with open('test.wav', 'rb') as f:
#    r = requests.post( url, data=f )

#r = requests.post(url = url, files = files)

#print( r.text )



url = 'http://123.57.79.160:8088/handle'

files = { 'file': open('test.wav', 'rb') }
#files = { 'file': open('test.opus', 'rb') }
#files = { 'file': open('test.mp3', 'rb') }

r = requests.post(url, files=files)
#print(r.text)


#r = requests.post("http://123.57.79.160/handle")
print(str(r))
print( r.status_code )

if r.status_code == 200:
    with open('test3.wav', 'wb') as f:
        f.write( r.content )



