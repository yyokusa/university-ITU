from repository.Database import Database
from Model.User import User
import views
from flask import Flask
from dl_model import DLModel

def create_app():
    app = Flask(__name__)

    app.add_url_rule("/", view_func=views.index, methods=["GET", "POST"])
    app.add_url_rule("/notifications", view_func=views.notifications, methods=["GET", "POST"])
    app.add_url_rule("/update", view_func=views.update_patient_medical_data, methods=["GET", "POST"]) 

    #app.add_url_rule("/profile", view_func=views.show_profile, methods=["GET", "POST"]) show_profile
    app.add_url_rule("/profile", view_func=views.show_profile, methods=["GET", "POST"])
    #app.add_url_rule("/pre<int:patient_id>", view_func=views.pre_patient, methods=["GET", "POST"])
    app.add_url_rule("/add_patient", view_func=views.insert_patient, methods=["GET", "POST"])

    app.add_url_rule("/login", view_func=views.login, methods=["GET", "POST"])
    app.add_url_rule("/logout", view_func=views.logout, methods=["GET", "POST"])
    app.add_url_rule("/register", view_func=views.register, methods=["GET", "POST"])
    app.add_url_rule("/patient/<int:patient_id>", view_func=views.patient_profile, methods=["GET", "POST"])
    # app.add_url_rule("/notifications/<int:user_key>", view_func=views.look_request, methods=["GET", "POST"])

    app.add_url_rule("/notifications/<int:user_key>/<int:notification_key>", view_func=views.examine_patient_info,
                     methods=["GET", "POST"])

    app.secret_key = 'super secret key'
    app.config['SESSION_TYPE'] = 'filesystem'

    db = Database()
    dlmodel = DLModel()

    app.config["db"] = db
    app.config["dlmodel"] = dlmodel
    app.config["log"] = False
    return app


if __name__ == '__main__':
    app = create_app()
    app.run(debug=True)

