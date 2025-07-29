from flask import Blueprint, request, render_template
import os

input_bp = Blueprint('input', __name__, url_prefix='/input', template_folder='templates')

@input_bp.route('/', methods=['GET', 'POST'])
def index():
    data = None
    file_path = 'blueprints\input\latest.txt'  # Atur path relatif terhadap root project

    if request.method == 'POST':
        aktivitas = request.form.get("aktivitas")
        if aktivitas:
            with open(file_path, 'w') as f:
                f.write(aktivitas)
            data = aktivitas

    elif request.method == 'GET' and os.path.exists(file_path):
        with open(file_path, 'r') as f:
            data = f.read()

    return render_template('index.html', data=data)