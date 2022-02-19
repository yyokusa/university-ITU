from flask_login import UserMixin


class UserModel(UserMixin):
    def __init__(self, username, password, email, name=None, surname=None, created=None, country_id=None, userid=None):
        self.username = username
        self.password = password
        self.email = email
        self.name = name
        self.surname = surname
        self.created = created
        self.country_id = country_id
        self.id = userid
