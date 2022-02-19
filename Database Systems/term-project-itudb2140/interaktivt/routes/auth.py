from flask import Blueprint
from flask import render_template
from flask import redirect
from flask import url_for
from flask import request
from flask import flash
from flask_login import login_user, login_required, logout_user
from werkzeug.security import generate_password_hash, check_password_hash
from ..repository.UserRepository import UserRepository
from ..repository.Database import Database

auth = Blueprint('auth', __name__)


@auth.route('/login')
def login():
    return render_template('login.html')


@auth.route('/login', methods=['POST'])
def login_post():
    # login code goes here
    email = request.form.get('email')
    password = request.form.get('password')
    remember = True if request.form.get('remember') else False

    user = UserRepository.fetch_user(email=email)

    # check if the user actually exists
    # take the user-supplied password, hash it, and compare it to the hashed password in the database
    if not user or not check_password_hash(user.password, password):
        flash('Please check your login details and try again.')
        return redirect(url_for('auth.login'))  # if the user doesn't exist or password is wrong, reload the page

    # if the above check passes, then we know the user has the right credentials
    login_user(user, remember=remember)
    return redirect(url_for('main.profile'))


@auth.route('/signup')
def signup():
    return render_template('signup.html')


@auth.route('/signup', methods=['POST'])
def signup_post():
    email = request.form.get('email')
    username = request.form.get('username')
    password = request.form.get('password')

    user = UserRepository.fetch_user(email=email)

    # A user with identical email already exists, redirect back to signup page for retry
    if user:
        flash('Email address already exists')
        return redirect(url_for('auth.signup'))

    # creating new user
    result = UserRepository.insert_user(email=email, username=username,
                                        password=generate_password_hash(password, method='sha256'))
    if result:
        return redirect(url_for('auth.login'))

    return redirect(url_for('auth.signup'))


@auth.route('/logout')
@login_required
def logout():
    logout_user()
    return redirect(url_for('main.index'))
