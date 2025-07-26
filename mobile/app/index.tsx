import React, { useEffect, useRef } from 'react';
import { StyleSheet, View, Text, SafeAreaView } from 'react-native';
import MapView, { Region, PROVIDER_GOOGLE, Marker } from 'react-native-maps';
import { useSensorData } from './hooks/useSensorData';
import { initNotificationHandler } from './services/notification';
import { MaterialCommunityIcons } from '@expo/vector-icons'

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
    <SafeAreaView style={styles.container}>
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
        <View style={ styles.infoPanel }>
          <Text style={ styles.lastUpdated }>Last Updated : <Text style= { styles.timeUpdated }>Just Now</Text>
          </Text>
          <View style= { styles.allPanel }>
            <View style= { styles.heartratePanel}>
              <View style= {styles.circlePanel}>
                <Text style={styles.bigText} >97%</Text>
              </View>
              <Text style={styles.label}>SpO₂</Text>
            </View>

            <View style= { styles.spO2Panel}>
              <View style= {styles.circlePanel}>
                <Text style={styles.bigText}>97</Text>
                <Text style={styles.smallText}>bpm</Text>
              </View>
              <Text style={styles.label}>HeartRate</Text>
            </View>

            <View style= { styles.harPanel}>
              <View style= { styles.harBox}>
                <Text style= { styles.harLabel }>Human Activity Recognition</Text>
                <View style= { styles.harRow }>
                  <MaterialCommunityIcons name="run" size={60} color="black" style= {{flex: 1}} />
                  <Text style= {{ flex: 1, color: 'blue', fontWeight:'bold'}}>Running</Text>
                </View>
              </View>
            </View>
          </View>
        </View>
      )}
    </SafeAreaView>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#ffff',
  },
  map: {
    height: '70%',
    width: '100%',
  },
  infoPanel:{
    flex: 1 ,
    backgroundColor: '#ffff',
    borderTopLeftRadius: 20,
    borderTopRightRadius: 20,
    padding: 20,
  },
  lastUpdated: {
    fontSize: 18,
    fontWeight: 'bold',
    color: '#333'
  },
  timeUpdated: {
    color: 'green',
    textDecorationLine: 'underline'
  },
  allPanel: {
    flex: 1,
    flexDirection: 'row',
  },
  heartratePanel: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center'
  },
  spO2Panel: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center'
  },
  circlePanel: {
    width: 80,
    height: 80,
    borderRadius: 40,
    backgroundColor: '#e0e0e0ff',
    justifyContent: 'center',
    alignItems: 'center',
    elevation: 2,
  },
  label: {
    fontSize: 16,
    fontWeight: 500,
    color: '#333'
  },
  smallText: {
    fontSize: 14,
    fontWeight: 500,
    color: '#333'
  },
  bigText:{
    fontSize: 30,
    fontWeight: 500,
    color: '#333'
  },
  harPanel: {
    flex: 2,
    justifyContent: 'center',
    alignItems: 'center'
  },
  harBox: {
    width: 160,
    height: 100,
    borderRadius: 20,
    backgroundColor: '#e0e0e0ff',
    justifyContent: 'flex-start',
    alignItems: 'center',
    elevation: 2,
    padding: 10
  },
  harLabel:{
    fontSize: 10,
    fontWeight: 500,
    color: '#333'
  },
  harRow: {
    flex: 1,
    flexDirection: 'row',
    justifyContent: 'center', 
    alignItems: 'center'
  }
});
