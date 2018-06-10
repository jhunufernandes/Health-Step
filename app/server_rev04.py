# -*- coding: utf-8 -*-
# Coded by: Shuji & Jhunu | Health Step

from flask import Flask, render_template, request
from subprocess import call
import os
import pyrebase

config = {
    "apiKey": "AIzaSyDSsHJRtdLaiVn-7gQdGrqFIS4INm8S8Gk",
    "authDomain": "sancathon-4775b.firebaseapp.com",
    "databaseURL": "https://sancathon-4775b.firebaseio.com",
    "projectId": "sancathon-4775b",
    "storageBucket": "sancathon-4775b.appspot.com",
    "messagingSenderId": "109188504367"
}

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
        file_database.close()
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
        file_database.close()
    for line in range(len(database)):
        if(post in database[line]):
            return database[line][1]
    return 0

def cloud_format(cloud_data):
    file_database = open("database.ods","r")
    database_raw = file_database.readlines()
    database = []
    for line in range(len(database_raw)):
        data = database_raw[line]
        data = data[:-3]
        data = data.split(",")
        database.append(data)
        file_database.close()

    for line in range(len(database)):
        cloud_data.append({})

    for line in range(len(database)):
        for element in range(len(database[0])):
            chave = str(database[0][element])
            cloud_data[line][chave] = str(database[line][element])
    return cloud_data

about_text = "oi"

firebase = pyrebase.initialize_app(config)
cloud_data = []
app = Flask(__name__)

auth = firebase.auth()
user = auth.sign_in_with_email_and_password('jhunu.fernandes@gmail.com',123456)
db = firebase.database()

def firebase_update(cloud_data):
    db = firebase.database()
    cloud_data = cloud_format(cloud_data)
    print cloud_data
    for element in cloud_data:
        ID = element['ID']
        db.child("Users").child(ID).set(element,user['idToken'])

@app.route('/')
def home():
    return render_template('home.html')

@app.route('/about')
def about():
    return render_template('about.html', about = about_text)

@app.route('/auth', methods=['GET', 'POST'])
def auth():
    if request.method == 'POST': #this block is only entered when the form is submitted
        post = request.form.get('id')
        prioridade = int(query_auth(str(post)))
        if prioridade == 0:
            return render_template('about.html')
        if prioridade in [1,2,3,4]:
            return render_template('result_data.html')
        if prioridade == 5:
            info = query_database(str(post))
            return render_template("result_public.html", nome = info[2], alergia = info[5], doenca = info[6], sangue = info[8], contato = info[11])
    return render_template('auth.html')

@app.route('/data_show', methods = ['POST', 'GET'])
def data_show():
   if request.method == 'POST':
      info_request = request.form.get('id')
      info = query_database(str(info_request))
      return render_template("data_show.html", nome = info[2], cpf = info[4], alergia = info[5], doenca = info[6], medicamento = info[7], sangue = info[8], historico = info[9], convenio = info[10], contato = info[11])

@app.route('/add', methods=['GET', 'POST'])
def add():
    if request.method == 'POST': #this block is only entered when the form is submitted
        post = request.form.get('id')
        prioridade = int(query_auth(str(post)))
        if prioridade in [1,2,3,4]:
            return render_template('add_result.html')
        else:
            return render_template('restrict.html')
    return render_template('auth.html')

@app.route('/data_add', methods = ['POST', 'GET'])
def data_add():
    if request.method == 'POST':
        text_add = ''
        for id in range(12):
            text_add = text_add + ',' + request.form.get('id'+str(id))
        text_add = text_add[1:] + '$\n'
        file = open("update.txt", "w")
        file.write(text_add)
        file.close()
        call(["./step-health", "-a", "update.txt"])
        # return render_template('about.html')
        firebase_update(cloud_data)
        return render_template('home.html')

if __name__ == '__main__':
    app.run(host = '0.0.0.0',debug=True)
