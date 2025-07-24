from pydantic import BaseModel
from typing import List

class dataValidator(BaseModel):
    heartrate   :float
    spO2        :float
    mpu6050     :List[float]
    longitude   :float 
    latitude    :float