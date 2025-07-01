from flask import Blueprint,request
from blueprints.data.utility.dataReceive import dataReceive
from blueprints.data.utility.dataShow import dataShow

data_bp = Blueprint('data', __name__)

@data_bp.route("/", methods=['GET','POST'])
def index():
    if request.method == 'POST':
        return dataReceive()
    elif request.method == 'GET':
        return dataShow()
    else :
        return "<h1>Data Invalid</h1>"

