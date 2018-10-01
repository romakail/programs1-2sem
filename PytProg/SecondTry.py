import vk

#[){
#from Data import MyVkData as d

ROMA_UID = '142973536'
MY_UID = '471617778'
API_URL = 'https://api.vk.com/method/'

session = vk.Session()
vkapi = vk.API(session)

friends = vkapi.friends.get(user_id = ROMA_UID, count = 20, fields = 'photo')


#print (friends[0] )
i = 0
while i < 20:
	print(friends[i]['photo'])
	print('\n')
	i = i + 1

