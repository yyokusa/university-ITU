import psycopg2
from datetime import datetime, timezone
from flask import current_app as app
from ..model.User import UserModel

"""
    def __init__(self, username, password, email, name=None, surname=None, created=None, country_id=None, userid=None):
        self.username = username
        self.password = password
        self.email = email
        self.name = name
        self.surname = surname
        self.created = created
        self.country_id = country_id
        self.id = userid
        """


def generate_user_object(username, password, email, name, surname, created, country_id, userid):
    return UserModel(username=username,
                     password=password,
                     email=email,
                     name=name,
                     surname=surname,
                     created=created,
                     country_id=country_id,
                     userid=userid, )


class UserRepository:
    # pass
    @staticmethod
    def fetch_user(email):
        db = app.config['db']
        cursor = db.connection.cursor()
        cursor.execute('SELECT * FROM  public."user"  WHERE email = %s', (email,))
        query_result = cursor.fetchone()  # returning a single tuple, or None
        cursor.close()
        if query_result:
            return generate_user_object(username=query_result[1],
                                        password=query_result[2],
                                        email=query_result[4],
                                        name=query_result[5],
                                        surname=query_result[6],
                                        created=query_result[3],
                                        country_id=query_result[7],
                                        userid=query_result[0], )
        return None

    @staticmethod
    def fetch_user_id(user_id):
        db = app.config['db']
        print('connection: ', db)
        print('connection TYPE: ', type(db))
        cursor = db.connection.cursor()
        cursor.execute('SELECT * FROM  public."user"  WHERE id = %s', (user_id,))
        query_result = cursor.fetchone()  # returning a single tuple, or None
        cursor.close()
        if query_result:
            return generate_user_object(username=query_result[1],
                                        password=query_result[2],
                                        email=query_result[4],
                                        name=query_result[5],
                                        surname=query_result[6],
                                        created=query_result[3],
                                        country_id=query_result[7],
                                        userid=query_result[0], )
        return None

    @staticmethod
    def insert_user(email, username, password):
        db = app.config['db']
        print('connection: ', db)
        print('connection TYPE: ', type(db))
        cursor = db.connection.cursor()

        # created = datetime.now(timezone.utc)
        user = generate_user_object(username=username,
                                    password=password,
                                    email=email)

        record_to_insert = (user.email,
                            user.username,
                            user.password,
                            user.location)

        try:
            cursor.execute(' INSERT INTO public."user" \
                                (email, username, password, location) \
                                VALUES (%s,%s,%s,%s)', record_to_insert)
            db.connection.commit()
            count = cursor.rowcount
            print(count, "Record inserted successfully into user table")
            result = True
        except (Exception, psycopg2.Error) as error:
            # Always check for specific errors in except block
            db.connection.rollback()
            print("Failed to insert new user", error)
            result = False
        finally:
            cursor.close()
            return result

    @staticmethod
    def update_user(email, new_email, new_username, new_location):
        db = app.config['db']
        cursor = db.connection.cursor()

        try:
            cursor.execute('''  UPDATE public."user" SET  \
                                email=%s, username=%s, location=%s \
                                WHERE email=%s''', (new_email, new_username, new_location, email))
            db.connection.commit()
            count = cursor.rowcount
            print(count, "Record updated successfully into user table")
            result = True
        except (Exception, psycopg2.Error) as error:
            db.connection.rollback()
            print("Failed to update new user", error)
            result = False
        finally:
            cursor.close()
            return result

    @staticmethod
    def delete_user(email):
        db = app.config['db']
        cursor = db.connection.cursor()

        try:
            cursor.execute('''  DELETE FROM public."user"  \
                                WHERE email=%s''', (email,))
            db.connection.commit()
            count = cursor.rowcount
            print(count, "Record deleted successfully from user table")
            result = True
        except (Exception, psycopg2.Error) as error:
            db.connection.rollback()
            print("Failed to delete user", error)
            result = False
        finally:
            cursor.close()
            return result
