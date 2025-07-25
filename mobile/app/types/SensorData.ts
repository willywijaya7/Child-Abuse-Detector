import { Float } from "react-native/Libraries/Types/CodegenTypes";

export interface SensorData {
  timestamp: string;
  max30100: {
    heartrate: Float;
    spO2: Float;
  };
  classification: string;
  'gt-u7': {
    longitude: Float;
    latitude: Float;
  };
}
