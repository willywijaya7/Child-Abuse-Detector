from pydantic import BaseModel

class dataValidator(BaseModel):
    timestamp   :str
    heartrate   :float
    spO2        :float
    gyroX       :float
    gyroY       :float
    gyroZ       :float
    acceX       :float
    acceY       :float
    acceZ       :float
    longitude   :float 
    latitude    :float