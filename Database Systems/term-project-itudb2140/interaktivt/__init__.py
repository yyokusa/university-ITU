from flask import Flask
from flask_login import LoginManager
from .repository.Database import Database
import uuid


def create_app():
    app = Flask(__name__)
    app.config['SECRET_KEY'] = uuid.uuid4().hex
    app.config.from_envvar('INTERAKTIVT_SETTINGS')

    db = Database(
        user=app.config['USER'],
        password=app.config['PASSWORD'],
        host=app.config['HOST'],
        port=app.config['PORT'],
        database=app.config['DATABASE']
    )
    app.config["db"] = db
    # login
    '''
        If a visitor makes a request to a protected page without logging in,
        we can redirect the request to the login page by setting the 
        login_view property of the login manager.
    '''
    login_manager = LoginManager()
    login_manager.login_view = 'auth.login'
    login_manager.init_app(app)

    from .repository.UserRepository import UserRepository

    @login_manager.user_loader
    def load_user(user_id):
        # since the user_id is just the primary key of our user table, use it in the query for the user
        return UserRepository.fetch_user_id(int(user_id))

    # blueprint for auth routes in our app
    from .routes.auth import auth as auth_bp
    app.register_blueprint(auth_bp)

    # blueprint for non-auth parts of app
    from .routes.main import main as main_bp
    app.register_blueprint(main_bp)

    # blueprint for crud parts of app
    from .routes.crud import crud as crud_bp
    app.register_blueprint(crud_bp)

    return app



