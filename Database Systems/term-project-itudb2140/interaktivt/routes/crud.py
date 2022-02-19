from flask import Blueprint, render_template
from flask_login import login_required, current_user
from flask import request, json
from flask import flash
from ..repository import CountryRepository, HdiRepository, HistoricalRepository
from flask import redirect
from flask import url_for

crud = Blueprint('crud', __name__)


@crud.route('/crud')
def operations():
    return render_template('crud.html')


@crud.route('/add_country', methods=['POST'])
@login_required
def add_country():
    print(request.data)
    if request.get_json():  # None or json
        json_data = request.get_json(silent=True)
        # print(json_data)
        name = json_data['name']
        hdi_rank = json_data['hdi_rank']
        result = CountryRepository.insert_country(name, hdi_rank)
        if result:
            redirect(url_for('main.countries'))
            return json.dumps({'success': True}), 200, {'ContentType': 'application/json'}

        flash('Something went wrong.')
        redirect(url_for('crud.operations'))
        return json.dumps({'success': False}), 500, {'ContentType': 'application/json'}

    else:
        name = request.form.get('name')
        hdi_rank = request.form.get('hdi_rank')

        result = CountryRepository.insert_country(name, hdi_rank)
        if result:
            return redirect(url_for('main.countries'))

        flash('Something went wrong.')
        return redirect(url_for('crud.operations'))


@crud.route('/delete_country', methods=['POST'])
@login_required
def delete_country():
    name = request.form.get('name')

    result = CountryRepository.delete_country(name)
    if result:
        return redirect(url_for('main.countries'))

    flash('Something went wrong.')
    return redirect(url_for('crud.operations'))



@crud.route('/update_country', methods=['POST'])
@login_required
def update_country():
    # new_name, new_hdi_rank, name
    name = request.form.get('name')
    new_name = request.form.get('new_name')
    new_hdi_rank = request.form.get('new_hdi_rank')

    result = CountryRepository.update_country(new_name, new_hdi_rank, name)
    if result:
        return redirect(url_for('main.countries'))

    flash('Something went wrong.')
    return redirect(url_for('crud.operations'))

@crud.route('/insert_hdi', methods=['POST'])
@login_required
def insert_hdi():
    # country_id, hdi, life, education_e, education_m, gnhd, gni
    name = request.form.get('name')
    country_id = CountryRepository.fetch_country(name).id
    hdi = request.form.get('hdi')
    life = request.form.get('life')
    education_e = request.form.get('education_e')
    education_m = request.form.get('education_m')
    gnhd = request.form.get('gnhd')
    gni = request.form.get('gni')

    result = HdiRepository.insert_hdi(country_id, hdi, life, education_e, education_m, gnhd, gni)
    if result:
        return redirect(url_for('main.countries'))

    flash('Something went wrong.')
    return redirect(url_for('crud.operations'))


@crud.route('/update_hdi', methods=['POST'])
@login_required
def update_hdi():
    # country_id, hdi, life, education_e, education_m, gnhd, gni
    name = request.form.get('name')
    country_id = CountryRepository.fetch_country(name).id
    hdi = request.form.get('hdi')
    life = request.form.get('life')
    education_e = request.form.get('education_e')
    education_m = request.form.get('education_m')
    gnhd = request.form.get('gnhd')
    gni = request.form.get('gni')

    result = HdiRepository.update_hdi(country_id, hdi, life, education_e, education_m, gnhd, gni)
    if result:
        return redirect(url_for('main.countries'))

    flash('Something went wrong.')
    return redirect(url_for('crud.operations'))


@crud.route('/delete_hdi', methods=['POST'])
@login_required
def delete_hdi():
    # country_id
    name = request.form.get('name')
    country_id = CountryRepository.fetch_country(name).id

    result = HdiRepository.delete_hdi(country_id)
    if result:
        return redirect(url_for('main.countries'))

    flash('Something went wrong.')
    return redirect(url_for('crud.operations'))


@crud.route('/insert_historical', methods=['POST'])
@login_required
def insert_historical():
    name = request.form.get('name')
    country_id = CountryRepository.fetch_country(name).id
    year1990 = request.form.get('year1990')
    year2000 = request.form.get('year2000')
    year2010 = request.form.get('year2010')
    year2011 = request.form.get('year2011')
    year2012 = request.form.get('year2012')
    year2013 = request.form.get('year2013')

    result = HistoricalRepository.insert_historical(country_id, year1990, year2000, year2010, year2011, year2012, year2013)
    if result:
        return redirect(url_for('main.countries'))

    flash('Something went wrong.')
    return redirect(url_for('crud.operations'))


@crud.route('/update_historical', methods=['POST'])
@login_required
def update_historical():
    name = request.form.get('name')
    country_id = CountryRepository.fetch_country(name).id
    year1990 = request.form.get('year1990')
    year2000 = request.form.get('year2000')
    year2010 = request.form.get('year2010')
    year2011 = request.form.get('year2011')
    year2012 = request.form.get('year2012')
    year2013 = request.form.get('year2013')

    result = HistoricalRepository.update_historical(country_id, year1990, year2000, year2010, year2011, year2012, year2013)
    if result:
        return redirect(url_for('main.countries'))

    flash('Something went wrong.')
    return redirect(url_for('crud.operations'))


@crud.route('/delete_historical', methods=['POST'])
@login_required
def delete_historical():
    name = request.form.get('name')
    country_id = CountryRepository.fetch_country(name).id

    result = HistoricalRepository.delete_historical(country_id)
    if result:
        return redirect(url_for('main.countries'))

    flash('Something went wrong.')
    return redirect(url_for('crud.operations'))
