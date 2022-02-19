import psycopg2
from flask import current_app as app
from ..model.Country import CountryModel

"""

class CountryModel:
    def __init__(self, name, hdi_rank, country_id=None):
        self.name = name
        self.hdi_rank = hdi_rank
        self.id = country_id

        """


def fetch_country(name):
    db = app.config['db']
    cursor = db.connection.cursor()
    cursor.execute('SELECT * FROM  public."country"  WHERE name = %s', (name,))
    query_result = cursor.fetchone()  # returning a single tuple, or None
    cursor.close()
    if query_result:
        return CountryModel(name=query_result[0],
                            hdi_rank=query_result[1],
                            country_id=query_result[2])
    return None


def fetch_country_all():
    db = app.config['db']
    cursor = db.connection.cursor()
    cursor.execute('SELECT * FROM  public."country"')
    query_results = cursor.fetchall()  # returning a single tuple, or None
    cursor.close()
    if query_results:
        return [CountryModel(name=query_result[0],
                             hdi_rank=query_result[1],
                             country_id=query_result[2]) for query_result in query_results]
    return None


def insert_country(name, hdi_rank):
    db = app.config['db']
    print('connection: ', db)
    print('connection TYPE: ', type(db))
    cursor = db.connection.cursor()

    record_to_insert = (name,
                        hdi_rank)

    try:
        cursor.execute(' INSERT INTO public."country" \
                            (name, hdi_rank) \
                            VALUES (%s,%s)', record_to_insert)
        db.connection.commit()
        count = cursor.rowcount
        print(count, "Record inserted successfully into country table")
        result = True
    except (Exception, psycopg2.Error) as error:
        db.connection.rollback()
        print("Failed to insert new country", error)
        result = False
    finally:
        cursor.close()
        return result


def update_country(new_name, new_hdi_rank, name):
    db = app.config['db']
    cursor = db.connection.cursor()

    try:
        cursor.execute('''  UPDATE public."country" SET  \
                            name=%s, hdi_rank=%s \
                            WHERE name=%s''', (new_name, new_hdi_rank, name))
        db.connection.commit()
        count = cursor.rowcount
        print(count, "Record updated successfully into country table")
        result = True
    except (Exception, psycopg2.Error) as error:
        db.connection.rollback()
        print("Failed to update country", error)
        result = False
    finally:
        cursor.close()
        return result


def delete_country(name):
    db = app.config['db']
    cursor = db.connection.cursor()

    try:
        cursor.execute('''  DELETE FROM public."country"  \
                            WHERE name=%s''', (name,))
        db.connection.commit()
        count = cursor.rowcount
        print(count, "Record deleted successfully from country table")
        result = True
    except (Exception, psycopg2.Error) as error:
        db.connection.rollback()
        print("Failed to delete country", error)
        result = False
    finally:
        cursor.close()
        return result
