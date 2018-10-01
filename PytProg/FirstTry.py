import requests
import json

#from Data import MyVkData as d

ROMA_UID = '142973536'
MY_UID = '471617778'
API_URL = 'https://api.vk.com/method/'

response = requests.get (API_URL+'friends.get', {'user_id':ROMA_UID})
result = response.text
response = json.loads(result)

print (response)

