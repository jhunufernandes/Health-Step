# -*- coding: utf-8 -*-
# Coded by: Jhunu | Health Step

from flask import Flask, render_template, request

about_text = ""

app = Flask(__name__)

@app.route('/')
def home():
  return render_template('home.html')

@app.route('/about')
def about():
  return render_template('about.html', about = about_text)

@app.route('/data')
def data():
  return render_template('data.html')

@app.route('/auth', methods=['GET', 'POST'])
def auth():
    data = request.form.get('id')
    if request.method == 'POST': #this block is only entered when the form is submitted
            # ABRIR APLICACAO CONSULTA NO BANCO
                # RETORNA O PRIORIDADE
            # SWITCH CASE PRIORIDADE
            # RENDERIZA TEMPLATE ESPECIFICO
        return data
    return render_template('auth.html')

if __name__ == '__main__':
  app.run(debug=True)
