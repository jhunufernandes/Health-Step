from flask import Flask, render_template, request

app = Flask(__name__)

@app.route('/')
def home():
  return render_template('home.html')

@app.route('/about')
def about():
  return render_template('about.html')

@app.route('/data')
def data():
  return render_template('data.html')

@app.route('/auth', methods=['GET', 'POST']) #allow both GET and POST requests
def auth():
    if request.method == 'POST': #this block is only entered when the form is submitted
        return render_template('data.html')
    return render_template('auth.html')


if __name__ == '__main__':
  app.run(debug=True)
