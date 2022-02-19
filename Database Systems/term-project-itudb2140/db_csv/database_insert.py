from interaktivt.repository.Database import Database
from interaktivt.model.Country import CountryModel
import pandas as pd
import psycopg2

db = Database(
    user='postgres',
    password='yasin123',
    host='0.0.0.0',
    port='5432',
    database='postgres'
)


def insert_country(name, hdi_rank):
    cursor = db.connection.cursor()

    try:
        cursor.execute(' INSERT INTO public."country" \
                            (name, hdi_rank) \
                            VALUES (%s,%s)', (name, hdi_rank,))
        db.connection.commit()
        count = cursor.rowcount
        print(count, "Record inserted successfully into user table")
        result = True
    except (Exception, psycopg2.Error) as error:
        # Always check for specific errors in except block
        db.connection.rollback()
        print("Failed to insert new country", error)
        result = False
    finally:
        cursor.close()
        return result


def insert_hdi(country_id,
               hdi,
               life,
               education_e,
               education_m,
               gnhd,
               gni, ):
    cursor = db.connection.cursor()

    try:
        cursor.execute(' INSERT INTO public."human_development" \
                            (country_id, hdi, life, education_e, education_m, gnhd, gni) \
                            VALUES (%s, %s, %s, %s, %s, %s, %s)',
                       (country_id, hdi, life, education_e, education_m, gnhd, gni))
        db.connection.commit()
        count = cursor.rowcount
        print(count, "Record inserted successfully into user table")
        result = True
    except (Exception, psycopg2.Error) as error:
        # Always check for specific errors in except block
        db.connection.rollback()
        print("Failed to insert new hdi", error)
        result = False
    finally:
        cursor.close()
        return result


def insert_historical(year1990,
                      year2000,
                      year2010,
                      year2011,
                      year2012,
                      year2013,
                      country_id, ):
    cursor = db.connection.cursor()

    try:
        cursor.execute(' INSERT INTO public."historical_index" \
                            ("1990","2000","2010","2011","2012","2013", country_id) \
                            VALUES (%s, %s, %s, %s, %s, %s, %s)',
                       (year1990, year2000, year2010, year2011, year2012, year2013, country_id,))
        db.connection.commit()
        count = cursor.rowcount
        print(count, "Record inserted successfully into hist idx table")
        result = True
    except (Exception, psycopg2.Error) as error:
        # Always check for specific errors in except block
        db.connection.rollback()
        print("Failed to insert new historical index record", error)
        result = False
    finally:
        cursor.close()
        return result


counter = 0
# countries = pd.read_csv('./db_csv/countries.csv').to_numpy()
# for country in countries:
#     result = insert_country(*((country[1:])[::-1]))
#     if result:
#         counter += 1

# hdis = pd.read_csv('./db_csv/hdi_cleaned.csv').to_numpy()
# for hdi in hdis:
#     hdi = list((hdi[-1], *hdi[:-1]))
#     result = insert_hdi(*hdi)
#     if result:
#         counter += 1


hists = pd.read_csv('./db_csv/hist_cleaned.csv').to_numpy()
for hist in hists:
    result = insert_historical(*hist)
    if result:
        counter += 1


print('Succesfull inserts: ', counter)
