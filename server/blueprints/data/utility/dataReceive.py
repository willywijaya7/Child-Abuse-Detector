from flask import request,jsonify
from pydantic import ValidationError
from blueprints.data.utility.dataValidator import dataValidator
from datetime import datetime
import pytz

def dataReceive():
    try:
        dataJson=request.get_json()
        utcTime = datetime.now(pytz.utc)
        timestamp = utcTime.astimezone(pytz.timezone("Asia/Jakarta")).isoformat()
        # TAMBAHKAN CODINGAN UNTUK HANDLE
        validated = dataValidator(
            heartrate=dataJson['max30100']['heartrate'],
            spO2=dataJson['max30100']['spO2'],
            mpu6050=dataJson['mpu6050'],
            longitude=dataJson['gt-u7']['longitude'],
            latitude=dataJson['gt-u7']['latitude']
        )
        # with open ("blueprints/data/storage/file.txt", "a") as file:
        #     file.write(f"{timestamp},{validated.heartrate},{validated.spO2},{validated.longitude},{validated.latitude}\n")
        data = None
        with open('blueprints/input/latest.txt', 'r') as file:
            data = file.read()
        with open ("blueprints/data/storage/file2.txt", "a") as file:
            file.write(f"{timestamp},{data},{validated.mpu6050}\n")
        return jsonify({
            "status" : "success",
        }),200
    except ValidationError as ve:
        return jsonify({
            "status": "validation error",
            "errors": ve.errors()
        }), 400
    except Exception as e:
        print("Exception:", e)
        return jsonify({
            "status": "error",
            "message": str(e)
        }), 400


if __name__ == "__main__":
    dataReceive()
