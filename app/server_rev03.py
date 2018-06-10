# -*- coding: utf-8 -*-
# Coded by: Shuji & Jhunu | Health Step

from flask import Flask, render_template, request


def query_database(info_request):
    file_database = open("database.ods","r")
    database_raw = file_database.readlines()
    database = []

    for line in range(len(database_raw)):
        data = database_raw[line]
        data = data[:-3]
        data = data.split(",")
        for element in range(len(data)):
            data[element] = str(data[element])
        database.append(data)

    for line in range(len(database)):
        if info_request in database[line]:
            return database[line]


def query_auth(post):
    file_database = open("database.ods","r")
    database_raw = file_database.readlines()
    database = []

    for line in range(len(database_raw)):
        data = database_raw[line]
        data = data[:-3]
        data = data.split(",")
        database.append(data)

    for line in range(len(database)):
        if(post in database[line]):
            return database[line][1]
    return 0


about_text = "oi"

app = Flask(__name__)

@app.route('/')
def home():
    return render_template('home.html')

@app.route('/about')
def about():
    return render_template('about.html', about = about_text)

@app.route('/result_data')
def result_data():
    return render_template('result_data.html')


@app.route('/auth', methods=['GET', 'POST'])
def auth():
    post = request.form.get('id')
    if request.method == 'POST': #this block is only entered when the form is submitted
        prioridade = int(query_auth(post))
        if prioridade == 0:
            return render_template('notfound.html')
        if prioridade in [1,2,3,4]:
            return render_template('result_data.html')
        if prioridade == 5:
            info = query_database(str(post))
            return render_template("result_public.html", nome = info[2], alergia = info[5], doenca = info[6], sangue = info[8], contato = info[11])
            # return render_template('result_public.html')
    return render_template('auth.html')

@app.route('/data_show', methods = ['POST', 'GET'])
def data_show():
   if request.method == 'POST':
      info_request = request.form.get('id')
      info = query_database(str(info_request))
      return render_template("data_show.html", nome = info[2], cpf = info[4], alergia = info[5], doenca = info[6], medicamento = info[7], sangue = info[8], historico = info[9], convenio = info[10], contato = info[11])


if __name__ == '__main__':
    app.run(host = '0.0.0.0',debug=True)
