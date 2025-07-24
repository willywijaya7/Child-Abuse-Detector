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
            "gt-u7": {
                "longitude" : data[3],
                "latitude" : data[4]
            },
            "classification" : data[5]
        },
        indent=4
    )

if __name__ == "__main__":
    dataShow()