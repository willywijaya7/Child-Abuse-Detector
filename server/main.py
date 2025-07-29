from flask import Flask, Blueprint
from blueprints.data.data import data_bp
from blueprints.input.input import input_bp

app = Flask(__name__)
app.register_blueprint(data_bp, url_prefix="/datas")
app.register_blueprint(input_bp, url_prefix="/input")

if __name__ == "__main__":
    app.run(debug=True)