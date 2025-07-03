import axios from 'axios';
import React, { useEffect, useRef, useState} from 'react';
import { StyleSheet, View, Text } from 'react-native';
import MapView, { Region, PROVIDER_GOOGLE , Marker} from 'react-native-maps';
import { SensorData } from './types/SensorData'; 

const API_URL = 'https://d5e5-203-24-50-227.ngrok-free.app/datas';

const INITIAL_REGION: Region = {
  latitude: 0.0,
  longitude: 0.0,
  latitudeDelta: 0.1,
  longitudeDelta: 0.1,
};

export default function App() {
  const [data, setData] = useState<SensorData | null>(null);
  const mapRef = useRef<MapView>(null);

  // Fetch data from Flask backend
  useEffect(() => {
    fetchData();
    const interval = setInterval(fetchData, 1000);
    return () => clearInterval(interval);
  }, []);

  const fetchData = async () => {
    try {
      const response = await axios.get(API_URL);
      const resData = response.data;

      const convertedData: SensorData = {
        ...resData,
        'gt-u7': {
          latitude: parseFloat(resData['gt-u7'].latitude),
          longitude: parseFloat(resData['gt-u7'].longitude),
        },
      };
      setData(convertedData);
    } catch (error) {
      console.error('Error fetching data:', error);
    }
  };

  // Animate map to new data when it changes
  useEffect(() => {
    if (data && mapRef.current) {
      mapRef.current.animateToRegion({
        latitude: data['gt-u7'].latitude,
        longitude: data['gt-u7'].longitude,
        latitudeDelta: 0.01,
        longitudeDelta: 0.01,
      });
    }
  }, [data]);

  return (
    <View style={styles.container}>
      <MapView
        style={styles.map}
        initialRegion={INITIAL_REGION}
        provider={PROVIDER_GOOGLE}
        ref={mapRef}>
        {data && (
          <Marker
            coordinate={{
              latitude: data['gt-u7'].latitude,
              longitude: data['gt-u7'].longitude,
          }}></Marker>
          )}
      </MapView>

      {data && (
        <View style={styles.infoPanel}>
          <Text style={styles.mode}>🚶 Monitoring Aktif</Text>
          <Text style={styles.metric}>❤️ Heart Rate: {data?.max30100.heartrate || '-'} bpm</Text>
          <Text style={styles.metric}>🩸 SpO2: {data?.max30100.spO2 || '-'} %</Text>
        </View>  
      )}
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: "#ffff"
  },
  map: {
    height: '60%',
    width: '100%',
  },
  infoPanel: {
    flex: 1,
    padding: 20,
    backgroundColor: '#fff',
    borderTopLeftRadius: 20,
    borderTopRightRadius: 20,
    elevation: 5,
  },
  mode: {
    fontSize: 18,
    fontWeight: 'bold',
    marginBottom: 10,
  },
  metric: {
    fontSize: 16,
    marginBottom: 5,
  },
});