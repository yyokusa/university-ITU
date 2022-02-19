import psycopg2
from flask import current_app as app
from ..model.HDI import HDIModel
from ..model.Country_HDI import CountryHdiModel


def fetch_record(name):
    db = app.config['db']
    cursor = db.connection.cursor()

    cursor.execute('''select * from country c, human_development hd \
                        where hd.country_id = c.id \
                        and c.name = %s;''', (name,))
    query_result = cursor.fetchone()  # returning a single tuple, or None
    cursor.close()
    if query_result:
        return HDIModel(country_id=query_result[1],
                        hdi=query_result[2],
                        life=query_result[3],
                        education_e=query_result[4],
                        education_m=query_result[5],
                        gnhd=query_result[6],
                        gni=query_result[7],
                        _id=query_result[0])
    return None


def fetch_record_all():
    db = app.config['db']
    cursor = db.connection.cursor()

    cursor.execute('''select * from country c, human_development hd \
                        where hd.country_id = c.id;''')
    query_results = cursor.fetchall()
    cursor.close()
    if query_results:
        return [CountryHdiModel(name=query_result[0],
                                hdi_rank=query_result[1],
                                country_id=query_result[2],
                                hd_id=query_result[3],
                                hdi=query_result[4],
                                life=query_result[5],
                                education_e=query_result[6],
                                education_m=query_result[7],
                                gnhd=query_result[8],
                                gni=query_result[9], ) for query_result in query_results]
    return None


def insert_hdi(country_id, hdi, life, education_e, education_m, gnhd, gni):
    db = app.config['db']
    print('connection: ', db)
    print('connection TYPE: ', type(db))
    cursor = db.connection.cursor()

    record_to_insert = (country_id,
                        hdi,
                        life,
                        education_e,
                        education_m,
                        gnhd,
                        gni,)

    try:
        cursor.execute(' INSERT INTO public."human_development" \
                            (country_id, hdi, life, education_e, education_m, gnhd, gni) \
                            VALUES (%s, %s, %s, %s, %s, %s, %s)', record_to_insert)
        db.connection.commit()
        count = cursor.rowcount
        print(count, "Record inserted successfully into hdi table")
        result = True
    except (Exception, psycopg2.Error) as error:
        db.connection.rollback()
        print("Failed to insert new hdi", error)
        result = False
    finally:
        cursor.close()
        return result


def update_hdi(country_id, hdi, life, education_e, education_m, gnhd, gni):
    db = app.config['db']
    cursor = db.connection.cursor()

    try:
        cursor.execute('''  UPDATE public."human_development" SET  \
                            hdi=%s, life=%s, education_e=%s, education_m=%s, gnhd=%s, gni=%s \
                            WHERE country_id=%s''', (hdi, life, education_e, education_m, gnhd, gni, country_id))
        db.connection.commit()
        count = cursor.rowcount
        print(count, "Record updated successfully into hdi table")
        result = True
    except (Exception, psycopg2.Error) as error:
        db.connection.rollback()
        print("Failed to update hdi", error)
        result = False
    finally:
        cursor.close()
        return result


def delete_hdi(country_id):
    db = app.config['db']
    cursor = db.connection.cursor()

    try:
        cursor.execute('''  DELETE FROM public."human_development"  \
                            WHERE country_id=%s''', (country_id,))
        db.connection.commit()
        count = cursor.rowcount
        print(count, "Record deleted successfully from hdi table")
        result = True
    except (Exception, psycopg2.Error) as error:
        db.connection.rollback()
        print("Failed to delete hdi", error)
        result = False
    finally:
        cursor.close()
        return result
