from flask import request,json,jsonify
from pydantic import ValidationError
from blueprints.data.utility.dataValidator import dataValidator

def dataReceive():
    try:
        dataJson=request.get_json()
        validated = dataValidator(
            timestamp=dataJson['timestamp'],
            heartrate=dataJson['max30100']['heartrate'],
            spO2=dataJson['max30100']['spO2'],
            gyroX= dataJson['mpu6050']['gyroscope']['x'],
            gyroY= dataJson['mpu6050']['gyroscope']['y'],
            gyroZ= dataJson['mpu6050']['gyroscope']['z'],
            acceX= dataJson['mpu6050']['accelerometer']['x'],
            acceY= dataJson['mpu6050']['accelerometer']['y'],
            acceZ= dataJson['mpu6050']['accelerometer']['z'],
            longitude=dataJson['gt-u7']['longitude'],
            latitude=dataJson['gt-u7']['latitude']
        )
        with open ("blueprints/data/storage/file.txt", "a") as file:
            file.write(f"{validated.timestamp},{validated.heartrate},{validated.spO2},{validated.gyroX},{validated.gyroY},{validated.gyroZ},{validated.acceX},{validated.acceY},{validated.acceZ},{validated.longitude},{validated.latitude}\n")
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
