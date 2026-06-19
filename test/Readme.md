# ความรู้เบื้องต้นเกี่ยวกับเซ็นเซอร์ (Sensor Fundamentals)

## 1. เซ็นเซอร์คืออะไร?

เซ็นเซอร์ (Sensor) คืออุปกรณ์ที่ตรวจจับหรือวัดปริมาณทางกายภาพจากสิ่งแวดล้อม แล้วแปลงเป็นสัญญาณไฟฟ้าที่ระบบประมวลผลสามารถอ่านได้

```
Physical Quantity → [Sensor] → Electrical Signal → [Microcontroller] → Output
```

---

## 2. ประเภทของสัญญาณเซ็นเซอร์

| ประเภท | คำอธิบาย | ตัวอย่าง |
|--------|-----------|----------|
| **Analog** | สัญญาณต่อเนื่อง (0–5V, 0–3.3V) | เทอร์มิสเตอร์, LDR, Potentiometer |
| **Digital** | สัญญาณ HIGH/LOW (0 หรือ 1) | PIR, สวิตช์, Hall Effect |
| **PWM** | สัญญาณพัลส์ความถี่คงที่ | Servo feedback, บางเซ็นเซอร์วัดระยะ |
| **Protocol** | สื่อสารผ่านโปรโตคอล | DHT22 (1-Wire), BMP280 (I2C), MAX6675 (SPI) |

---

## 3. เซ็นเซอร์ที่พบบ่อยในงาน Embedded

### 3.1 เซ็นเซอร์อุณหภูมิ

| เซ็นเซอร์ | อินเทอร์เฟซ | ย่านวัด | ข้อดี |
|----------|------------|---------|-------|
| LM35 | Analog | -55 ถึง 150°C | ราคาถูก ใช้งานง่าย |
| DHT11 | Digital 1-Wire | 0–50°C | มี Humidity ในตัว |
| DHT22 | Digital 1-Wire | -40 ถึง 80°C | แม่นยำกว่า DHT11 |
| DS18B20 | 1-Wire Protocol | -55 ถึง 125°C | ต่อได้หลายตัวบนสายเดียว |
| PT100/PT1000 | Analog (ต้องการ amplifier) | -200 ถึง 850°C | แม่นยำสูง ใช้งานอุตสาหกรรม |
| Thermocouple K | SPI (MAX6675/MAX31855) | -200 ถึง 1350°C | วัดอุณหภูมิสูงมาก |

### 3.2 เซ็นเซอร์ความดัน

| เซ็นเซอร์ | อินเทอร์เฟซ | การใช้งาน |
|----------|------------|----------|
| BMP180 | I2C | ความดันบรรยากาศ, ระดับความสูง |
| BMP280 | I2C/SPI | แม่นยำกว่า BMP180 |
| MPX5010 | Analog | วัดความดันน้ำ/ก๊าซ |

### 3.3 เซ็นเซอร์ระยะทาง

| เซ็นเซอร์ | หลักการ | ย่านวัด |
|----------|---------|---------|
| HC-SR04 | Ultrasonic | 2–400 cm |
| VL53L0X | Laser ToF (I2C) | 3–200 cm |
| IR Sharp GP2Y0A21 | Infrared Analog | 10–80 cm |

### 3.4 เซ็นเซอร์ความชื้น

- **DHT11 / DHT22** — วัดความชื้นสัมพัทธ์ (RH) และอุณหภูมิในชิปเดียว
- **HIH6130** — I2C, แม่นยำสูง

### 3.5 เซ็นเซอร์แสง

| เซ็นเซอร์ | ประเภท | หมายเหตุ |
|----------|--------|---------|
| LDR (GL5516) | Analog Resistive | ค่าต้านทานแปรตามแสง |
| BH1750 | I2C (lux) | วัดค่าความสว่างเป็น lux |
| VEML6070 | I2C (UV) | วัดรังสี UV |
| TSL2561 | I2C | ใกล้เคียงการมองเห็นของมนุษย์ |

---

## 4. โปรโตคอลการสื่อสารของเซ็นเซอร์

### I2C (Inter-Integrated Circuit)
- สายสัญญาณ: **SDA** (Data) + **SCL** (Clock)
- ต่อได้หลายอุปกรณ์บนบัสเดียว (แต่ละตัวมี address ไม่ซ้ำกัน)
- ความเร็ว: 100 kHz (Standard), 400 kHz (Fast)

```
MCU ──SDA──┬── Sensor A (0x40)
           ├── Sensor B (0x76)
    ──SCL──┘
```

### SPI (Serial Peripheral Interface)
- สายสัญญาณ: **MOSI**, **MISO**, **SCK**, **CS**
- ความเร็วสูงกว่า I2C, แต่ใช้สายมากกว่า
- ใช้บ่อยกับ: MAX6675, MAX31855, ADXL345

### UART (Universal Asynchronous Receiver-Transmitter)
- สายสัญญาณ: **TX**, **RX**
- ใช้กับ: GPS module, Bluetooth HC-05, เซ็นเซอร์ PM2.5

### 1-Wire
- ใช้สายเดียว (Data) ต่อหลายอุปกรณ์
- ใช้กับ: DS18B20 (อุณหภูมิ)

---

## 5. วงจรพื้นฐาน: Voltage Divider สำหรับ Analog Sensor

เซ็นเซอร์แบบ Resistive (LDR, Thermistor, PT100) ต้องใช้ Voltage Divider เพื่อแปลงค่าต้านทานเป็นแรงดัน

```
VCC (3.3V หรือ 5V)
  │
  R_fixed (ตัวต้านทานคงที่)
  │
  ├──── ADC Pin (อ่านค่าแรงดัน)
  │
  R_sensor (เซ็นเซอร์)
  │
GND
```

สูตร:
```
V_out = VCC × R_sensor / (R_fixed + R_sensor)
```

---

## 6. การแปลงค่า ADC เป็นค่าจริง

ไมโครคอนโทรลเลอร์อ่านค่า ADC เป็นตัวเลข เช่น 0–1023 (10-bit) หรือ 0–4095 (12-bit)

```cpp
// ตัวอย่าง Arduino (10-bit ADC, VCC = 5V)
int raw = analogRead(A0);           // 0 – 1023
float voltage = raw * (5.0 / 1023.0);  // แปลงเป็นแรงดัน (V)
```

สำหรับ LM35 (10 mV/°C):
```cpp
float temperature = voltage * 100.0;  // 1V = 100°C
```

---

## 7. ข้อควรระวังในการใช้งานเซ็นเซอร์

| ปัญหา | สาเหตุ | วิธีแก้ |
|-------|--------|---------|
| ค่าอ่านสั่นไหว (Noisy) | สัญญาณรบกวน, ADC ไม่เสถียร | ใส่ capacitor bypass 100nF, ทำ averaging |
| ค่าผิดพลาดจาก Offset | เซ็นเซอร์ไม่ผ่านการ calibrate | Calibration กับค่าอ้างอิง |
| Pull-up/Pull-down | I2C/1-Wire ไม่มีแรงดันอ้างอิง | ต่อ pull-up resistor 4.7kΩ |
| Logic Level Mismatch | เซ็นเซอร์ 5V ต่อกับ MCU 3.3V | ใช้ Logic Level Converter |
| Warm-up Time | เซ็นเซอร์บางตัวต้องอุ่นเครื่อง | รอ delay ก่อนอ่านค่า |

---

## 8. Transducer vs Sensor

| คำศัพท์ | ความหมาย |
|--------|---------|
| **Sensor** | ตรวจจับปริมาณทางกายภาพ → สัญญาณไฟฟ้า (อ่านอย่างเดียว) |
| **Actuator** | สัญญาณไฟฟ้า → ปริมาณทางกายภาพ (ขับเคลื่อน) |
| **Transducer** | คำรวม: อุปกรณ์ที่แปลงพลังงานจากรูปหนึ่งไปอีกรูปหนึ่ง (ครอบคลุมทั้ง Sensor และ Actuator) |

---

## 9. ตัวอย่างโค้ด PlatformIO (ESP32 + DHT22)

```cpp
#include <Arduino.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(115200);
    dht.begin();
}

void loop() {
    float humidity    = dht.readHumidity();
    float temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    Serial.printf("Temp: %.1f°C  Humidity: %.1f%%\n", temperature, humidity);
    delay(2000);
}
```

---

*อ้างอิง: Datasheet DHT22, DS18B20, BMP280 | PlatformIO Documentation*
