# 📏 IMPLEMENTASI SENSOR ULTRASONIK / PING PADA ARDUINO UNO
![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)
![Ultrasonic](https://img.shields.io/badge/Sensor-Ultrasonic-blue?style=for-the-badge)
![Version](https://img.shields.io/badge/Version-1.0-green?style=for-the-badge)

## 🔧 Komponen & Pin Konfigurasi

| Komponen          | Pin Arduino | Keterangan            |
|-------------------|-------------|----------------------|
| Push Button       | D2          | Mode Control         |
| LED               | D3          | PWM Compatible       |
| Buzzer            | D8          | Alert System         |
| PING Trigger      | D12         | Ultrasonic Trigger   |
| PING Echo         | D13         | Ultrasonic Echo      |
| LCD I2C (SDA)     | A4          | Data I2C             |
| LCD I2C (SCL)     | A5          | Clock I2C            |

## 🎯 Mode Operasi

### Mode 1: Monitoring Dasar PING 📊
```plaintext
[Tekan Tombol #1]
```
- Aktivasi sensor ultrasonic
- Display jarak real-time di LCD
- Monitoring detail via serial monitor
- Format tampilan: "Jarak: XX cm"

### Mode 2: Sistem Peringatan 🚨
```plaintext
[Tekan Tombol #2]
```
- Monitoring jarak dengan threshold
- Aktivasi buzzer saat melewati batas
- Peringatan di LCD dan serial monitor
- Ideal untuk sistem keamanan jarak

### Mode 3: Visualisasi LED 💡
```plaintext
[Tekan Tombol #3]
```
- LED fading berbasis PWM
- Intensitas sesuai pembacaan jarak
- Display LCD dan serial monitor aktif
- Representasi visual dari pengukuran

### Mode 4: Reset Sistem 🔄
```plaintext
[Tekan Tombol #4]
```
- Kembali ke Mode 1
- Reset semua output
- Sistem siap untuk siklus baru

## 📊 Mode Detail

### Mode 1: Monitoring
- Pengukuran kontinu
- Refresh rate: 500ms
- Format LCD: "Jarak: XXX cm"
- Serial output: "Distance: XXX cm"

### Mode 2: Peringatan
- Threshold default: 20cm
- Buzzer pattern: Continuous
- Warning message di LCD
- Log events di serial

### Mode 3: LED Visualization
- PWM mapping: 0-255
- Inverse relationship dengan jarak
- Smooth fading effect
- Real-time distance display

## 🔍 Troubleshooting

1. **Pembacaan Tidak Stabil**
   - Cek koneksi kabel
   - Pastikan power supply stabil
   - Hindari noise ultrasonic

2. **LCD Tidak Tampil**
   - Verifikasi alamat I2C
   - Cek koneksi SDA/SCL
   - Test dengan I2C scanner
