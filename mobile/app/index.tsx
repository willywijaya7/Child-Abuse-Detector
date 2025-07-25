import React, { useEffect, useRef } from 'react';
import { StyleSheet, View, Text } from 'react-native';
import MapView, { Region, PROVIDER_GOOGLE, Marker } from 'react-native-maps';
import { useSensorData } from './hooks/useSensorData';
import { initNotificationHandler } from './services/notification';

const INITIAL_REGION: Region = {
  latitude: 0.0,
  longitude: 0.0,
  latitudeDelta: 0.1,
  longitudeDelta: 0.1,
};

export default function App() {
  const data = useSensorData();
  const mapRef = useRef<MapView>(null);

  useEffect(() => {
    initNotificationHandler();
  }, []);

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
            }}
          />
        )}
      </MapView>

      {data && (
        <View style={styles.infoPanel}>
          <Text style={styles.mode}>🚶 Monitoring Aktif</Text>
          <Text style={styles.metric}>❤️ Heart Rate: {data.max30100.heartrate || '-'} bpm</Text>
          <Text style={styles.metric}>🩸 SpO2: {data.max30100.spO2 || '-'} %</Text>
        </View>
      )}
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#ffff',
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
