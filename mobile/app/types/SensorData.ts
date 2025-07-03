import { Float } from "react-native/Libraries/Types/CodegenTypes";

export interface SensorData {
  timestamp: string;
  max30100: {
    heartrate: Float;
    spO2: Float;
  };
  mpu6050: {
    gyroscope: {
      x: Float;
      y: Float;
      z: Float;
    };
    accelerometer: {
      x: Float;
      y: Float;
      z: Float;
    };
  };
  'gt-u7': {
    longitude: Float;
    latitude: Float;
  };
}
