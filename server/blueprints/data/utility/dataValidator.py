from pydantic import BaseModel
from typing import List

class dataValidator(BaseModel):
    heartrate   :float
    spO2        :float
    mpu6050     :str
    longitude   :float 
    latitude    :float