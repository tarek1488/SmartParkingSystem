import firebase_admin
from firebase_admin import credentials, db
from datetime import date
def upload_val_to_firebase(available_slots:int):
    

    cred = credentials.Certificate("firebase_secret.json")

    if not firebase_admin._apps:
        firebase_admin.initialize_app(cred, {
            "databaseURL": "https://smartgarageproject-7f82b-default-rtdb.firebaseio.com/"
        })
    ref = db.reference("/")
    ref.update({"free_slots" : available_slots})