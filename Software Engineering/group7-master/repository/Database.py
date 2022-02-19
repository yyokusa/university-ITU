import psycopg2

from datetime import datetime, timezone
from Model.User import User
from Model.PatientInfoTable import PatientInfoTable
from Model.Notification import Notification

from dl_model import DLModel

class Database:
    def __init__(self):

        try:
            # connection = psycopg2.connect(user="postgres",
            #                       password='yasin123',
            #                       host="localhost",
            #                       port="5432",
            #                       database="sweng")
            connection = psycopg2.connect(user="qdtereweqkkpyt",
                                          password='f7669b958c0b8a65a7ee98485091056ec0287ced52212356fa1653ef4e720ddc',
                                          host="ec2-34-254-120-2.eu-west-1.compute.amazonaws.com",
                                          port="5432",
                                          database="d5pmu60k9pl75s")

            self.connection = connection

        except (Exception, psycopg2.Error) as error:
            self.connection = None
            print("Failed to establish connection", error)

    def get_user_info(self, email):
        cursor = self.connection.cursor()
        cursor.execute('SELECT * FROM  public.user  WHERE email = %s', (email,))
        result = cursor.fetchone()
        cursor.close()
        return User(email=result[1],
                    age=result[2],
                    name=result[3],
                    surname=result[4],
                    password=result[5],
                    user_type=result[6],
                    id=result[0]) if result else None

    def insert_user(self, user):
        cursor = self.connection.cursor()
        record_to_insert = (user.email,
                            user.age,
                            user.name,
                            user.surname,
                            user.password,
                            user.user_type)

        try:
            cursor.execute(' INSERT INTO public.user \
                                (email, age, name, surname, password, user_type) \
                                VALUES (%s,%s,%s,%s,%s, %s)', record_to_insert)
            self.connection.commit()
            count = cursor.rowcount
            print(count, "Record inserted successfully into user table")
            result = True
        except (Exception, psycopg2.Error) as error:
            self.connection.rollback()
            print("\n\nFailed to insert new user\n", error)
            result = False
            cursor.close()
            return result, error
        finally:
            """
            cursor.close()
            return result
            """
            cursor.close()
            return result, None

    def get_patient_info(self, patient_id):
        cursor = self.connection.cursor()
        try:
            cursor.execute('''SELECT * FROM public.patient_info, public.user
                            WHERE public.user.id = patient_id
                                AND patient_id = %s''', (patient_id,))
        except (Exception, psycopg2.ProgrammingError) as error:
            print("\n\nFailed to execute patient info query\n", error)
            return
        result = cursor.fetchall()
        cursor.close()
        return [PatientInfoTable(patient_id=record[0],
                                 doctor_id=record[1],
                                 name=record[2],
                                 surname=record[3],
                                 email=record[4],
                                 password=record[5],
                                 age=record[6],
                                 gender=record[7],
                                 city=record[8],
                                 body_height=record[9],
                                 body_mass_index=record[10],
                                 body_weight=record[11],
                                 blood_pressure_risk=record[12],
                                 cholesterol_risk=record[13],
                                 confirmed=record[14],
                                 id=record[15],
                                 hemoglobin_a1c=record[18],
                                 high_density_lipoprotein_cholesterol=record[19],
                                 low_density_lipoprotein_cholesterol= record[20],
                                 total_cholesterol=record[21],
                                 triglycerides=record[22],
                                 calcium=record[23],
                                 carbon_dioxide=record[24],
                                 chloride=record[25],
                                 creatinine=record[26],
                                 glucose=record[27],
                                 potassium=record[28],
                                 sodium=record[29],
                                 urea_nitrogen=record[30],
                                 glomerular_filtration=record[31],
                                 microalbumin=record[32],
                                 fev1_fvc=record[33]
                                 )
                for record in result]

    def get_one_patient_info(self, patient_id):
        cursor = self.connection.cursor()
        try:
            cursor.execute('''SELECT * FROM public.patient, public.user
                            WHERE public.user.id = patient_id
                                AND patient_id = %s''', (patient_id,))
        except (Exception, psycopg2.ProgrammingError) as error:
            print("\n\nFailed to execute patient info query\n", error)
            return
        record = cursor.fetchone()
        cursor.close()
        return PatientInfoTable(patient_id=record[0],
                                doctor_id=record[1],
                                blood_type=record[2],
                                blood_pressure=record[3],
                                diagnosis=record[4],
                                patient_info_id=record[6],
                                email=record[8],
                                age=record[9],
                                name=record[10],
                                surname=record[11],
                                )

    def update_notification_status(self, patient_info_id, status):
        cursor = self.connection.cursor()
        try:
            cursor.execute('''UPDATE public.notification as n
                            SET status = %s
                            where n.id=%s''', (status, patient_info_id,))
            self.connection.commit()
            count = cursor.rowcount
            print(count, "Record updated successfully into notification table")
            result = True
        except (Exception, psycopg2.ProgrammingError) as error:
            print("\n\nFailed to execute patient info update query\n", error)
            result = False
        finally:
            cursor.close()
            return result
    
    def insert_notification(self,user_id,doctor_id):
        cursor = self.connection.cursor()
        record_to_insert = (doctor_id,user_id,False,)
        try:
           
            cursor.execute(' INSERT INTO public.notification (from_,to_,status) VALUES (%s, %s, %s)', record_to_insert)
            self.connection.commit()
            count = cursor.rowcount
            print(count, "Record inserted successfully into Notification table")
            result = True
        except (Exception, psycopg2.Error) as error:
            self.connection.rollback()
            print("\n\nFailed to insert new patient\n", error)
            result = False
        finally:
            cursor.close()
            return result



    def get_received_notifications(self, user_id):
        cursor = self.connection.cursor()
        cursor.execute('''
        SELECT u.id,u.email,u.name,u.surname,n.status,n.id FROM public.user as u
        JOIN public.notification as n ON  u.id=n.to_ where n.from_=%s
        ''', (user_id,))
        results = cursor.fetchall()
        cursor.close()
        person_list = []
        for result in results:
            print(result)
            person_list.append(Notification(email=result[1],
                                            name=result[2],
                                            surname=result[3],
                                            status=result[4],
                                            notif_id=result[5],
                                            _from=result[0],
                                            to=user_id))
        return person_list

    def get_specific_notification(self, doctor_id, patient_id):
        cursor = self.connection.cursor()
        cursor.execute('''
        SELECT u.id,u.email,u.name,u.surname,n.status,n.id FROM public.user as u
        JOIN public.notification as n ON  u.id=n.to_ where n.from_=%s and n.to_=%s
        ''', (doctor_id,patient_id,))
        result = cursor.fetchone()
        cursor.close()
        
        if result == None:
            return None
        
        person = (Notification(email=result[1],
                                            name=result[2],
                                            surname=result[3],
                                            status=result[4],
                                            notif_id=result[5],
                                            _from=result[0],
                                            to=patient_id))
        return person


    def get_received_notifications_to_patient(self, user_id):
        cursor = self.connection.cursor()
        cursor.execute('''
        SELECT u.id,u.email,u.name,u.surname,n.status,n.id FROM public.user as u
        JOIN public.notification as n ON  u.id=n.from_ where n.to_=%s
        ''', (user_id,))
        results = cursor.fetchall()
        cursor.close()
        person_list = []
        for result in results:
            print(result)
            person_list.append(Notification(email=result[1],
                                            name=result[2],
                                            surname=result[3],
                                            status=result[4],
                                            notif_id=result[5],
                                            _from=result[0],
                                            to=user_id))
        return person_list

    def update_medical_data(self, patient):
        cursor = self.connection.cursor()
        try:
            cursor.execute("UPDATE public.patient SET gender=%s, city=%s, body_height=%s, body_mass_index=%s, body_weight=%s where patient_id=%s",
                           (patient.gender, patient.city, int(patient.body_height), patient.body_mass_index, patient.body_weight, patient.patient_id,))
            self.connection.commit()
            count = cursor.rowcount
            print(count, "Record updated successfully into notification table")
            result = True
        except (Exception, psycopg2.ProgrammingError) as error:
            print("\n\nFailed to execute patient info update query\n", error)
            result = False
        finally:
            cursor.close()
            return result

    def get_patient(self, patient_id):
        cursor = self.connection.cursor()

        try:
            cursor.execute(" SELECT * FROM public.patient WHERE patient_id = %s", (str(patient_id), ))
            
            record = cursor.fetchone()
            
            result = PatientInfoTable(patient_id=record[0],
                                 doctor_id=record[1],
                                 name=record[2],
                                 surname=record[3],
                                 email=record[4],
                                 password=record[5],
                                 age=record[6],
                                 gender=record[7],
                                 city=record[8],
                                 body_height=record[9],
                                 body_mass_index=record[10],
                                 body_weight=record[11],
                                 confirmed=record[12],
                                 id=record[13],
                                 blood_pressure_risk=record[14],
                                 cholesterol_risk=record[15],
                                 hemoglobin_a1c=record[16],
                                 high_density_lipoprotein_cholesterol=record[17],
                                 low_density_lipoprotein_cholesterol= record[18],
                                 total_cholesterol=record[19],
                                 triglycerides=record[20],
                                 calcium=record[21],
                                 carbon_dioxide=record[22],
                                 chloride=record[23],
                                 creatinine=record[24],
                                 glucose=record[25],
                                 potassium=record[26],
                                 sodium=record[27],
                                 urea_nitrogen=record[28],
                                 glomerular_filtration=record[29],
                                 microalbumin=record[30],
                                 fev1_fvc=record[31]
                                 )
            

        except (Exception, psycopg2.Error) as error:
            self.connection.rollback()
            print("\n\nFailed to get the user\n", error)
            result = None
        finally:
            cursor.close()
            return result

    def get_notification(self, from_, to_):
        cursor = self.connection.cursor()

        try:
            cursor.execute(" SELECT * FROM public.notification WHERE from_ = " + str(from_) + " and to_ = " + str(to_))
        
            notif = cursor.fetchone()
            print(notif)
            result = notif

        except (Exception, psycopg2.Error) as error:
            self.connection.rollback()
            print("\n\nFailed to get the user\n", error)
            result = False
        finally:
            cursor.close()
            return result

    def insert_patient(self, user):
        cursor = self.connection.cursor()
        record_to_insert = (
                            user.patient_id     ,
                            user.doctor_id      ,
                            user.name           ,
                            user.surname        ,
                            user.email          ,
                            user.password       ,
                            user.age            ,
                            user.gender         ,
                            user.city           , 
                            user.id             
                            )

        try:
            print(user.patient_id, user.doctor_id ,user.name,user.surname,user.email ,user.password,user.age,user.gender ,user.city )
            print(type(user.age))
            print(type(user.doctor_id))
            cursor.execute(' INSERT INTO public."patient" \
                                (patient_id, doctor_id, name, surname, email, password, age, gender, city,id) \
                                VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s,%s)', record_to_insert)
            self.connection.commit()
            count = cursor.rowcount
            print(count, "Record inserted successfully into patient table")
            result = True
        except (Exception, psycopg2.Error) as error:
            self.connection.rollback()
            print("\n\nFailed to insert new patient\n", error)
            result = False
        finally:
            cursor.close()
            return result

    def get_predictions_blood(self, patient):
        cursor = self.connection.cursor()
        print(patient)
        try:
            cursor.execute("UPDATE public.patient SET blood_pressure_risk=%s where patient_id=%s",
                           (patient.blood_pressure_risk, patient.patient_id,))
            self.connection.commit()
            count = cursor.rowcount
            print(count, "Record updated successfully into patient table")
            result = True
        except (Exception, psycopg2.ProgrammingError) as error:
            print("\n\nFailed to execute patient info update query\n", error)
            result = False
        finally:
            cursor.close()
            return result

    def get_predictions_chol(self, patient):
        cursor = self.connection.cursor()
        print(patient)
        try:
            cursor.execute("UPDATE public.patient SET cholesterol_risk=%s where patient_id=%s",
                           (patient.cholesterol_risk, patient.patient_id,))
            self.connection.commit()
            count = cursor.rowcount
            print(count, "Record updated successfully into notification table")
            result = True
        except (Exception, psycopg2.ProgrammingError) as error:
            print("\n\nFailed to execute patient info update query\n", error)
            result = False
        finally:
            cursor.close()
            return result

    def delete_predictions(self,patient):
        cursor = self.connection.cursor()

        value = None
        try:
            cursor.execute("UPDATE public.patient SET blood_pressure_risk=%s, cholesterol_risk=%s where patient_id=%s",
                           (value, value , patient.patient_id,))
            self.connection.commit()
            count = cursor.rowcount
            print(count, "Record updated successfully into notification table")
            result = True
        except (Exception, psycopg2.ProgrammingError) as error:
            print("\n\nFailed to execute patient info update query\n", error)
            result = False
        finally:
            cursor.close()
            return result

    def get_doctors_patients(self, doctorid):
        cursor = self.connection.cursor()
        cursor.execute('''SELECT id,patient_id, name,email,surname FROM public.patient 
                            WHERE doctor_id = %s''', (doctorid,))
        results = cursor.fetchall()
        patients=[]
        for res in results:
            patients.append(PatientInfoTable(id=res[0],patient_id=res[1],  doctor_id=None, name=res[2], surname=res[4], email=res[3], password=None, age=None))

        cursor.close()
        return patients

    def get_patient_with_id(self, id):
        cursor = self.connection.cursor()

        try:
            str_patient_id = str(id)
            cursor.execute(" SELECT * FROM public.patient WHERE id = '" + str_patient_id + "'")
            
            record = cursor.fetchone()
            
            result = PatientInfoTable(patient_id=record[0],
                                 doctor_id=record[1],
                                 name=record[2],
                                 surname=record[3],
                                 email=record[4],
                                 password=record[5],
                                 age=record[6],
                                 gender=record[7],
                                 city=record[8],
                                 body_height=record[9],
                                 body_mass_index=record[10],
                                 body_weight=record[11],
                                 confirmed=record[12],
                                 blood_pressure_risk=record[14],
                                 cholesterol_risk=record[15],
                                 id=record[13],
                                 hemoglobin_a1c=record[16],
                                 high_density_lipoprotein_cholesterol=record[17],
                                 low_density_lipoprotein_cholesterol= record[18],
                                 total_cholesterol=record[19],
                                 triglycerides=record[20],
                                 calcium=record[21],
                                 carbon_dioxide=record[22],
                                 chloride=record[23],
                                 creatinine=record[24],
                                 glucose=record[25],
                                 potassium=record[26],
                                 sodium=record[27],
                                 urea_nitrogen=record[28],
                                 glomerular_filtration=record[29],
                                 microalbumin=record[30],
                                 fev1_fvc=record[31]
                                 )
            

        except (Exception, psycopg2.Error) as error:
            self.connection.rollback()
            print("\n\nFailed to get the user\n", error)
            result = None
        finally:
            cursor.close()
            return result