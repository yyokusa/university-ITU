import psycopg2
from flask import current_app as app
from ..model.Historical import HistoricalModel


def fetch_record(name):
    db = app.config['db']
    cursor = db.connection.cursor()

    cursor.execute('''select * from historical_index hi, country c
                        where c.id = hi.country_id
                        and c.name = %s''', (name,))
    query_result = cursor.fetchone()
    cursor.close()
    if query_result:
        return HistoricalModel(year1990=query_result[0],
                               year2000=query_result[1],
                               year2010=query_result[2],
                               year2011=query_result[3],
                               year2012=query_result[4],
                               year2013=query_result[5],
                               country_id=query_result[7])
    return None


def insert_historical(country_id,
                      year1990,
                      year2000,
                      year2010,
                      year2011,
                      year2012,
                      year2013):
    db = app.config['db']
    cursor = db.connection.cursor()

    record_to_insert = (year1990,
                        year2000,
                        year2010,
                        year2011,
                        year2012,
                        year2013,
                        country_id)

    try:
        cursor.execute(''' INSERT INTO public."historical_index" \
                            ("1990","2000","2010","2011","2012","2013", country_id) \
                            VALUES (%s, %s, %s, %s, %s, %s, %s)''', record_to_insert)
        db.connection.commit()
        count = cursor.rowcount
        print(count, "Record inserted successfully into historical table")
        result = True
    except (Exception, psycopg2.Error) as error:
        db.connection.rollback()
        print("Failed to insert new historical", error)
        result = False
    finally:
        cursor.close()
        return result


def update_historical(country_id,
                      year1990,
                      year2000,
                      year2010,
                      year2011,
                      year2012,
                      year2013):
    db = app.config['db']
    cursor = db.connection.cursor()

    try:
        cursor.execute('''  UPDATE public."historical_index" SET  \
                            "1990"=%s, "2000"=%s, "2010"=%s, "2011"=%s, "2012"=%s, "2013"=%s \
                            WHERE country_id=%s''',
                       (year1990, year2000, year2010, year2011, year2012, year2013, country_id))
        db.connection.commit()
        count = cursor.rowcount
        print(count, "Record updated successfully into historical table")
        result = True
    except (Exception, psycopg2.Error) as error:
        db.connection.rollback()
        print("Failed to update historical", error)
        result = False
    finally:
        cursor.close()
        return result


def delete_historical(country_id):
    db = app.config['db']
    cursor = db.connection.cursor()

    try:
        cursor.execute('''  DELETE FROM public."historical_index"  \
                            WHERE country_id=%s''', (country_id,))
        db.connection.commit()
        count = cursor.rowcount
        print(count, "Record deleted successfully from historical_index table")
        result = True
    except (Exception, psycopg2.Error) as error:
        db.connection.rollback()
        print("Failed to delete historical_index record", error)
        result = False
    finally:
        cursor.close()
        return result
