from flask import Flask, Blueprint
from blueprints.data.data import data_bp

app = Flask(__name__)
app.register_blueprint(data_bp, url_prefix="/datas")

if __name__ == "__main__":
    app.run(debug=True)