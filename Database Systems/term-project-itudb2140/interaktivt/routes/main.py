from flask import Blueprint, render_template
from flask_login import login_required, current_user
from ..repository.Database import Database
from flask import request
from ..repository.UserRepository import UserRepository
from ..repository import CountryRepository
from ..repository import HdiRepository
from ..repository import HistoricalRepository
from flask import redirect
from flask import url_for
import datetime

main = Blueprint('main', __name__)


@main.route('/countries')
def countries():
    _countries = CountryRepository.fetch_country_all()
    return render_template('countries.html', countries=_countries)


@main.route('/countries_hdindex')
def countries_hdindex():
    all_country_indexes = HdiRepository.fetch_record_all()
    return render_template('hdindex.html', all_country_indexes=all_country_indexes)


@main.route('/country_historical_hdindex/<country_name>')
def country_historical_hdindex(country_name):
    historical_hdindex = HistoricalRepository.fetch_record(country_name)
    return render_template('historical_hdindex.html', historical_hdindex=historical_hdindex, country_name=country_name)


@main.route('/')
def index():
    day = datetime.datetime.now()
    return render_template('index.html', day=day.strftime("%A"))


@main.route('/profile')
@login_required
def profile():
    return render_template('profile.html', username=current_user.username)


# UPDATE USER INFORMATION GET
@main.route('/update')
@login_required
def update():
    return render_template('update.html')


# UPDATE USER INFORMATION POST
@main.route('/update', methods=['POST'])
@login_required
def update_post():
    email = current_user.email
    new_email = request.form.get('email')
    new_username = request.form.get('username')
    new_location = request.form.get('password')
    result = UserRepository.update_user(email=email, new_email=new_email, new_username=new_username,
                                        new_location=new_location)
    if result:
        return redirect(url_for('main.profile'))

    return redirect(url_for('main.update'))


@main.route('/delete', methods=['POST', 'GET'])
@login_required
def delete_user():
    if request.method == "POST":
        email = current_user.email
        confirmation_answer = request.form.get('confirmation')
        if confirmation_answer == 'YES':
            redirect(url_for('auth.logout'))
            result = UserRepository.delete_user(email=email)

        if result:
            print('user deletion successfull')

        return redirect(url_for('main.delete_user'))
    else:
        return render_template('delete.html')
