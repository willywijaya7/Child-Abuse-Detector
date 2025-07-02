# 🛡️ Child Abuse Detector
Proyek ini terdiri dari tiga bagian utama :
1. **Perangkat Keras (ESP)** pada folder `hardware_main` – Mengambil data sensor dari MAX30100, MPU6050, dan GPS GT-U7. 
2. **Server (Python)** pada folder `server` – Menyediakan endpoint untuk menerima data via HTTP dan menyimpannya.
3. **Mobile App (Expo)** pada folder `mobile` – Menampilkan data dari server secara real-time.

## 🛠️ Instalasi
Ikuti langkah-langkah dibawah ini untuk menjalankan proyek ini secara lokal :
### 1. Clone repository
```
git clone git@github.com:willywijaya7/Child-Abuse-Detector.git
cd Child-Abuse-Detector
```
### 2. Jalankan Server
Create a virtual environment
``` 
python -m venv .venv
```
Activate the virtual environments
```
# Windows
.venv\Scripts\activate

# macOS and Linux
source .venv/bin/activate
```
Installing the dependecy
```
pip install -r requirements.txt
```
Run the server
```
python main.py
```
### 3. Testing Server
Setelah server berjalan, kamu bisa menguji endpoint `POST /datas` menggunakan Postman.

#### Body JSON
```
{
  "timestamp": "2025-06-30T12:00:00",
  "max30100": {
    "heartrate": 78.5,
    "spO2": 97.0
  },
  "mpu6050": {
    "gyroscope": {
      "x": 0.01,
      "y": 0.02,
      "z": 0.03
    },
    "accelerometer": {
      "x": 0.10,
      "y": 0.15,
      "z": 0.20
    }
  },
  "gt-u7": {
    "longitude": 109.123456,
    "latitude": -0.123456
  }
}
```
Jika kamu ingin menguji data yang akan diterima, kamu bisa menguji pada end point `GET /datas`

### 4. Menjalankan Aplikasi Mobile
Silahkan melakukan download pada aplikasi `Expo Go` di Playstore / AppStore pada handphone!