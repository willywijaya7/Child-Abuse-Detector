import axios from 'axios';
import { SensorData } from '../types/SensorData';

const API_URL = 'https://3ab55ccc00c7.ngrok-free.app/datas/';

export const fetchSensorData = async (): Promise<SensorData> => {
  const response = await axios.get(API_URL);
  const resData = response.data;

  const convertedData: SensorData = {
    ...resData,
    'gt-u7': {
      latitude: parseFloat(resData['gt-u7'].latitude),
      longitude: parseFloat(resData['gt-u7'].longitude),
    },
  };

  return convertedData;
};
