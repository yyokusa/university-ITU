import binascii
import hashlib
import os

from flask import flash
from flask import render_template, request, redirect, url_for, session, current_app
from Model.PatientInfoTable import PatientInfoTable

from Model.User import User
from dl_model import DLModel

def index():
    session['is_in_home']=True
    return render_template('main.html')

def logout():
    session.pop('is_in_home', None)  
    session.pop('loggedin', None) 
    session.pop('id', None) 
    session.pop('email', None) 
    session.pop('name', None) 
    session.pop('age', None)
    session.pop('isDoctor', None) 
    session.pop('p_id', None) 

    current_app.config["log"]=False
    return redirect(url_for('index'))
def login():
    session['is_in_home']=False
    msg = ''
    if request.method == 'POST' and 'email' in request.form and 'password' in request.form:
        email = request.form['email']
        password = request.form['password']
        db = current_app.config['db']
        account = db.get_user_info(email)
        
        if account:
            if account.password == password:
                session['loggedin'] = True
                current_app.config["log"] = True
                session['id'] = account.id
                session['email'] = account.email
                session['name'] = account.name
                session['surname'] = account.surname
                session['age'] = account.age
                session['isDoctor']=account.user_type==1
                msg = 'Logged in successfully !'
                flash(msg)
                if session['isDoctor']:
                    return redirect(url_for('show_profile'))
                else:
                    p = db.get_patient_with_id(session['id'])
                    session['p_id']=account.user_type=p.patient_id
                    return redirect(url_for('patient_profile',patient_id=p.patient_id))
            else:
                msg = 'Incorrect username / password !'
                flash(msg)
                return redirect(url_for('login'))

        else:
            msg = 'No account found!'
            flash(msg)
            return redirect(url_for('login'))
    print(msg)
    return render_template('login.html', msg=msg)


def notifications():
    session['is_in_home']=False
    print('session[\'id\']: ', session['id'])
    if session['loggedin'] is True:
        db = current_app.config['db']
        fetched_notifications = db.get_received_notifications(session['id'])
        print('Fetching notifications for doctor id session[\'id\']', session['id'])
        return render_template('notifications.html', notifications=fetched_notifications)
    else:
        return render_template('login.html')


# NOT: recorlar icin CRUD yaparken, BIR HASTANIN -> TEK DOKTORU olacagi seklinde uygulandi
# diger durumda isler karisabilir!! (bir hasta -> birden fazla doktor gibi)
# add flash messages # from ve notification id geliyor
def examine_patient_info(user_key, notification_key):
    session['is_in_home']=False
    # print("PATIENT Id: ", user_key, "NOTIF Id:", notification_key) # dogru
    
    if session['loggedin'] :
        db = current_app.config['db']
        p = db.get_patient(user_key)
        print("sdskskkksksksksk")

        wanted =  request.form.getlist('model')
        
        db.delete_predictions(p)

        if "blood" in wanted:
            dl_model = current_app.config['dlmodel']
            p = dl_model.predict_blood(p)
            db.get_predictions_blood(p)
            print("1")


        if "chol" in wanted:
            dl_model = current_app.config['dlmodel']
            p = dl_model.predict_chol(p)
            db.get_predictions_chol(p)
            print("1")
        
        #modeli çağır sonuç al

        notif = db.get_specific_notification(session['id'], p.id)
        if notif == None:
            db.insert_notification(p.id,session['id'])
        else:
            db.update_notification_status(notif.id, True)
        return redirect(url_for('patient_profile',patient_id=p.patient_id))
   



def verify_password(stored_password, provided_password):
   
    salt = stored_password[:64]
    stored_password = stored_password[64:]
    pwdhash = hashlib.pbkdf2_hmac('sha512', provided_password.encode('utf-8'), salt.encode('ascii'), 100000)
    pwdhash = binascii.hexlify(pwdhash).decode('ascii')
    return pwdhash == stored_password


def register():
    session['is_in_home']=False
    msg = ''
   
    if request.method == 'POST':
        email = request.form['email']
        age = request.form['age']
        name = request.form['name']
        surname = request.form['surname']
        password = request.form['password']
        #password = hash_password(password)

        user = User(email, age, name, surname, password, user_type=1)

        db = current_app.config['db']
        answer = db.insert_user(user)
        if answer[0]:
            msg = 'You have successfully registered '
            flash(msg)
            return redirect(url_for('login'))
        else:
            print(answer[1])
            idx = str(answer[1]).find("DETAIL")
            if idx != -1:
                msg = str(answer[1])[:idx].capitalize()
            else:
                msg = "Something went wrong"
            flash(msg)
            return redirect(url_for('register'))
            # return render_template('register.html')
    return render_template('register.html')


def hash_password(password):
    session['is_in_home']=False
    salt = hashlib.sha256(os.urandom(60)).hexdigest().encode('ascii')
    pwdhash = hashlib.pbkdf2_hmac('sha512', password.encode('utf-8'), salt, 100000)
    pwdhash = binascii.hexlify(pwdhash)
    return (salt + pwdhash).decode('ascii')


def update_notification_status(notificationID):
    session['is_in_home']=False
    if session['loggedin']:
        print(notificationID)
        current_app.config['db'].update_notification_status(notificationID)
        return notifications()


def update_patient_medical_data():
    session['is_in_home']=False
    print(request.method)
    if session['loggedin'] and request.method == 'POST':
        patient = PatientInfoTable(
                            request.form["patient_id"],
                            request.form["doctor_id"],
                            request.form["name"],
                            request.form["surname"],
                            request.form["email"],
                            None,
                            request.form["age"],                                 
                            request.form["gender"],                                 
                            request.form["city"],          
                            request.form["body_height"],
                            request.form["body_mass_index"],
                            request.form["body_weight"],
                            None,
                            None,
                            None,
                            None,
                            request.form["hemoglobin_a1c"],                      
                            request.form["high_density_lipoprotein_cholesterol"],
                            request.form["low_density_lipoprotein_cholesterol"], 
                            request.form["total_cholesterol"],                   
                            request.form["triglycerides"],                       
                            request.form["calcium"],                             
                            request.form["carbon_dioxide"],                      
                            request.form["chloride"],                            
                            request.form["creatinine"],                          
                            request.form["glucose"],                             
                            request.form["potassium"],                           
                            request.form["sodium"],                              
                            request.form["urea_nitrogen"],                       
                            request.form["glomerular_filtration"],               
                            request.form["microalbumin"],                        
                            request.form["fev1_fvc"])


        checker = current_app.config['db'].update_medical_data(patient)
        print("updatedd ya")
        print((checker))
        print(session['id'])
        print(patient.doctor_id)
        db = current_app.config['db']
        
        p = db.get_patient(patient.patient_id)
        print("yaptımmm",patient.patient_id)
        notif = db.get_specific_notification(patient.doctor_id, p.id)
        
        
       
        if notif != None:
            print(notif)
            db.update_notification_status(notif.id, False)
        else:
            print(patient.doctor_id)
            print(p.id)

            db.insert_notification(p.id, patient.doctor_id)

        if checker:
            msg = "Updated Succesfully"
            flash(msg)
        else:
            msg = "something went wrong"
            flash(msg)

        if session['isDoctor']== False:
            return render_template('update_patient_profile.html', info=patient, notification_id = None,isNotif=False)

        elif session['isDoctor']:
            print("buraya mi")
            db = current_app.config['db']
            # BURADA NOTIFICATIONI ALIP OKUNDU BILGISI VERILECEK
            #notif = db.get_notification(patient.doctor_id, patient.patient_id)
            #update_notification_status(notif.id)
            notif = 0
            return render_template('update_patient_profile.html', info=patient, notification_id = notif)
        else:
            print("else mi")

        

    #elif session['loggedin'] and request.method == 'GET':
        #print("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb")
        """
        if session['id'] == patient.patient_id:
                return render_template('update_patient_profile.html', info=patient, notification_id = None)

            elif session['id'] == patient.doctor_id:
                notif = current_app.config['db'].get_notification(patient.doctor_id, patient.patient_id)
                return render_template('update_patient_profile.html', info=patient, notification_id = notif)
        """


# Hasta profil (constraint ekle)
# Doctor Profil
# inspect ekle statusun yanına
# Doctor a bak notificationdan sonra
# Patient ekleme ekleme

def insert_patient():
    session['is_in_home']=False
    msg = ''
    if request.method == 'POST':

        # doctorid current session kulanılarak doktorun id si alınarak verilecek

        doctorid = session['id']
        patient_id = request.form['id']
        name = request.form['name']
        surname = request.form['surname']
        email = request.form['email']
        age = int(request.form['age'])
        password = patient_id + surname
                 
        user = User(name=name, surname=surname, email=email,password= password, age=age, user_type=2)

        
               #patient info ekle
        db = current_app.config['db']
        #insert user table
        #insert patient table

        answer = db.insert_user(user)
        
        if answer[0]:
            msg = 'You have successfully registered '
            userID=db.get_user_info(email)
            print(userID)
            user1 =PatientInfoTable(patient_id=patient_id,doctor_id=doctorid,name=name, surname=surname, email=email,password= password, age=age,id=userID.id)
            flash(msg)
            answer = db.insert_patient(user1)
            print
            if answer:
                msg = 'Patient is added, successfuly '
                flash(msg)
                # TODO:  "notificationsa değil patient profile gidecek"
                return render_template('update_patient_profile.html', info=user1, notification_id = None)
            else:
                msg = "Something went wrong"
                flash(msg)
                return redirect(url_for('insert_patient'))
                # return render_template('register.html')
           
        else:
            print(answer[1])
            idx = str(answer[1]).find("DETAIL")
            if idx != -1:
                msg = str(answer[1])[:idx].capitalize()
            else:
                msg = "Something went wrong"
            flash(msg)
            return redirect(url_for('insert_patient'))
            # return render_template('register.html')


        
    return render_template('add_patient.html')


def patient_profile(patient_id):
    session['is_in_home']=False
    msg = ''
    if request.method == 'POST':
        print(patient_id)
        """
        email = request.form['email']
        age = request.form['age']
        name = request.form['name']
        surname = request.form['surname']
        password = request.form['password']
        password = hash_password(password)

        user = User(email, age, name, surname, password, user_type=1)

        db = current_app.config['db']
        answer = db.insert_user(user)
        if answer[0]:
            msg = 'You have successfully registered '
            flash(msg)
            return redirect(url_for('login'))
        else:
            print(answer[1])
            idx = str(answer[1]).find("DETAIL")
            if idx != -1:
                msg = str(answer[1])[:idx].capitalize()
            else:
                msg = "Something went wrong"
            flash(msg)
            return redirect(url_for('register'))
            # return render_template('register.html')
        """

    #return render_template('patient_info.html')
    elif session['loggedin'] and request.method == 'GET':
        print("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA")
        db = current_app.config['db']
        patient = db.get_patient(patient_id)
        #patient = PatientInfoTable(p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11])

        #patient = get_prediction(patient)

        print(session['id'])
        print(patient.doctor_id)
        isNotif = False
        if session['isDoctor'] == False:
            notif = db.get_specific_notification(patient.doctor_id,patient.id)
            print(notif)
            if notif != None:
                isNotif = notif.status
            
            return render_template('update_patient_profile.html', info=patient, notification_id = None, isNotif=isNotif )

        elif session['isDoctor']:
            if (session['id'] == patient.doctor_id):
                notif = db.get_notification(patient.doctor_id, patient.id)
                print("geldim",patient.id)
                n_id=None
                if notif!=None:
                    n_id=notif[0]

                return render_template('update_patient_profile.html', info=patient, notification_id =n_id)
            else:
                fetched_notifications = db.get_received_notifications(session['id'])
                patients = db.get_doctors_patients(session['id'])
                nn=len(fetched_notifications)
                np=len(patients)
                return redirect(url_for('show_profile', notifs=fetched_notifications, numbe_of_notif=nn,patients =patients ,numbe_of_patients=np))
                

def show_profile():
    session['is_in_home']=False
    if session['loggedin']:
        db = current_app.config['db']
        notif = db.get_received_notifications(session['id'])
        patients = db.get_doctors_patients(session['id'])
        nn=len(notif)
        np=len(patients)
        
        print(patients)
        return render_template('show_doctor_profile.html',notifs=notif, numbe_of_notif=nn,patients =patients ,numbe_of_patients=np)


