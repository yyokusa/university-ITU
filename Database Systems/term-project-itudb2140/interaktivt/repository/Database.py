import psycopg2


class Database:
    def __init__(self, user, password, host, port, database):
        try:
            self.connection = psycopg2.connect(user=user,
                                               password=password,
                                               host=host,
                                               port=port,
                                               database=database)
            print("Successfully establish connection")
        except (Exception, psycopg2.Error) as error:
            self.connection = None
            print("Failed to establish connection", error)
