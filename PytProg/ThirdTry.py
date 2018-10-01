import vk
from Data import MyVkData as D

#[){_
#from Data import MyVkData as d

#session = vk.AuthSession(app_id=D.APP_ID, user_login=D.LOGIN, user_password=D.PASSWORD)
session = vk.AuthSession(access_token = D.ACCESS_TOKEN)
vkapi = vk.API(session)

person = vkapi.users.get (iser_ids = D.ROMA_UID, fields = 'photo_id')
print (person[0]['photo_id'])

#response = vkapi.wall.post (owner_id = D.GROUP_ID, message = 'Hello World', attachments = 'photo'+person[0]['photo_id'])
#print (response)

def postPhoto (myMessage, photoId):
	response = vkapi.wall.post (owner_id = D.GROUP_ID, message = myMessage	, attachments = 'photo'+photoId)
	print (response)
	return response

postPhoto ('Hello everyone', person[0]['photo_id'])

















	
