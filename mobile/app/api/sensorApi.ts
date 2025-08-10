import axios from "axios";
import { SensorData } from "../types/SensorData";

const API_URL = process.env.EXPO_PUBLIC_API_URL || "https://0f792f6d1d0e.ngrok-free.app/datas/";

export default async function fetchSensorData(): Promise<SensorData> {
  try {
    const response = await axios.get(API_URL);
    const resData = response.data;

    if (!resData["gt-u7"]) {
      throw new Error("Data gt-u7 tidak ditemukan di API");
    }

    const convertedData: SensorData = {
      ...resData,
      "gt-u7": {
        latitude: parseFloat(resData["gt-u7"].latitude),
        longitude: parseFloat(resData["gt-u7"].longitude),
      },
    };

    return convertedData;
  } catch (error) {
    console.error("Gagal fetch data sensor:", error);
    throw error;
  }
};
