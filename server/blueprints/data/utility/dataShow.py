from collections import deque
import json

def dataShow():
    with open ("blueprints/data/storage/file.txt", "r") as file:
        last_line = deque(file, maxlen=1).pop().strip()
    data = last_line.split(",")
    return json.dumps(
        {
            "timestamp" : data[0],
            "max30100" : {
                "heartrate" : data[1] ,
                "spO2" : data[2]
            },
            "mpu6050" :{
                "gyroscope":{
                    "x": data[3],
                    "y": data[4],
                    "z": data[5]
                },
                "accelerometer":{
                    "x": data[6],
                    "y": data[7],
                    "z": data[8]
                }
            },
            "gt-u7": {
                "longitude" : data[9],
                "latitude" : data[10]
            }
        }
    )

if __name__ == "__main__":
    dataShow()