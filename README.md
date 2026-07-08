# Transducer — LAB04: DHT11 + LCD I2C

โปรเจกต์ PlatformIO สำหรับ Arduino UNO R3 อ่านค่าอุณหภูมิและความชื้นจากเซ็นเซอร์ DHT11 แล้วแสดงผลบนจอ LCD 16x2 (I2C) พร้อมพิมพ์ผลลัพธ์ผ่าน Serial Monitor

## ฮาร์ดแวร์ที่ใช้

- Arduino UNO R3
- DHT11 (Temperature & Humidity Sensor)
- LCD 16x2 พร้อมโมดูล I2C (PCF8574, address `0x27`)
- ตัวต้านทาน Pull-up 10kΩ (ขา DATA ของ DHT11 → VCC)

## การต่อวงจร

| อุปกรณ์ | ขา | ต่อกับ Arduino |
|---------|----|-----------------|
| DHT11 VCC | ขา 1 | 5V |
| DHT11 DATA | ขา 2 | D4 (มี Pull-up 10kΩ ไป VCC) |
| DHT11 GND | ขา 4 | GND |
| LCD I2C SDA | — | A4 |
| LCD I2C SCL | — | A5 |

ดูรายละเอียดเพิ่มเติมที่ [test/design.md](test/design.md) และ [test/Readme.md](test/Readme.md)

## โครงสร้างโปรเจกต์

```
Transducer/
├── src/
│   └── main.cpp        # โค้ดหลัก: อ่านค่า DHT11 และแสดงผลบน LCD/Serial
├── test/
│   ├── design.md        # สรุปการต่อขา
│   └── Readme.md         # เอกสารประกอบ LAB03 DHT11
├── platformio.ini        # ค่าคอนฟิก PlatformIO (board, library dependencies)
└── README.md
```

## Libraries ที่ใช้ (ระบุใน platformio.ini)

- `adafruit/DHT sensor library @ ^1.4.6`
- `adafruit/Adafruit Unified Sensor @ ^1.1.9`
- `marcoschwartz/LiquidCrystal_I2C @ ^1.1.4`

## การทำงานของโปรแกรม

1. เริ่มต้น Serial (9600 baud), DHT11 และ LCD
2. วนอ่านค่าความชื้น/อุณหภูมิทุก 2 วินาที
3. ถ้าอ่านค่าไม่ได้ (NaN) จะแสดง `Sensor Error` บน LCD และพิมพ์คำเตือนทาง Serial
4. ถ้าอ่านสำเร็จ จะแสดงอุณหภูมิ (°C) และความชื้น (%RH) ทั้งบน LCD และ Serial Monitor

## วิธีใช้งาน (PlatformIO CLI)

```bash
# คอมไพล์
pio run

# อัปโหลดไปยังบอร์ด
pio run --target upload

# เปิด Serial Monitor
pio device monitor
```

## ข้อควรระวัง

- DHT11 อ่านค่าได้สูงสุด 1 ครั้ง/วินาที ห้าม delay ต่ำกว่านี้
- ต้องต่อ Pull-up 10kΩ ที่ขา DATA มิฉะนั้นจะอ่านค่าไม่ได้ (NaN)
- ตรวจสอบ address ของโมดูล I2C ให้ตรงกับ `0x27` (ใช้ I2C Scanner หากไม่แน่ใจ)
