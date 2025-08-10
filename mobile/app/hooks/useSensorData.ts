// hooks/useSensorData.ts
import { useEffect, useRef, useState } from 'react';
import fetchSensorData from '../api/sensorApi';
import { showLocalNotification } from '../services/notification';
import { SensorData } from '../types/SensorData';

export const useSensorData = () => {
  const [data, setData] = useState<SensorData | null>(null);
  const lastClassification = useRef<string | null>(null);

  useEffect(() => {
    const fetchLoop = () => {
      fetchSensorData()
        .then((result) => {
          setData(result);

          // Kirim notifikasi jika terjadi JATUH
          if (result.classification === 'falling' && lastClassification.current !== 'JATUH') {
            showLocalNotification('NOTIFIKASI BAHAYA', 'PENGGUNA JATUH');
          }

          lastClassification.current = result.classification;
        })
        .catch((err) => console.error('Fetch error:', err));
    };

    fetchLoop();
    const interval = setInterval(fetchLoop, 1000);
    return () => clearInterval(interval);
  }, []);

  return data;
};
