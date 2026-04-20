import firebase_admin
from firebase_admin import credentials, db

cred = credentials.Certificate("creds.json")
firebase_admin.initialize_app(cred, {"databaseURL": "https://iiitn-sda-python-default-rtdb.firebaseio.com/"})

ref = db.reference('/Tree')
data = ref.get()
print(data)

ref.update({"Animal":"Lion"})
data = ref.get()

print(data)