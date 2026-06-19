# รหัส 000000000 นาย อนุวัฒน์ สุชาโต
## แผนกเทคนิคคอมพิวเตอร์

# LAB03 DHT11

---

## 1. DHT11 คืออะไร?

![DHT11 Sensor](https://upload.wikimedia.org/wikipedia/commons/thumb/c/c9/DHT11_Sensor.jpg/220px-DHT11_Sensor.jpg)

DHT11 เป็นเซ็นเซอร์วัด **อุณหภูมิ** และ **ความชื้น** ในชิปเดียว ส่งข้อมูลผ่านสายสัญญาณเพียง 1 เส้น (Single-wire / 1-Wire Protocol)

---

## 2. ข้อมูลจำเพาะ (Specifications)

| พารามิเตอร์ | ค่า |
|------------|-----|
| แรงดันไฟเลี้ยง (VCC) | 3.3V – 5V DC |
| ย่านวัดอุณหภูมิ | 0 – 50 °C |
| ความแม่นยำอุณหภูมิ | ± 2 °C |
| ย่านวัดความชื้น (RH) | 20 – 90 % RH |
| ความแม่นยำความชื้น | ± 5 % RH |
| อินเทอร์เฟซ | Digital 1-Wire |
| อัตราการส่งข้อมูล | สูงสุด 1 ครั้ง / วินาที |
| กระแสใช้งาน | 0.3 mA (วัด), 60 µA (standby) |
| จำนวนขา | 4 ขา (VCC, Data, NC, GND) |

---

## 3. ขาของ DHT11

```
      DHT11
   ┌─────────┐
   │  ○ ○ ○ ○│
   └─────────┘
     │ │ │ │
     1 2 3 4

ขา 1 = VCC   → ไฟเลี้ยง 3.3V – 5V
ขา 2 = DATA  → สัญญาณข้อมูล (ต่อ Pull-up 10kΩ ถึง VCC)
ขา 3 = NC    → ไม่ใช้งาน (No Connect)
ขา 4 = GND   → กราวด์
```

---

## 4. การต่อวงจรกับ Arduino UNO

| DHT11 | Arduino UNO |
|-------|------------|
| VCC (ขา 1) | 5V |
| DATA (ขา 2) | D2 (+ R 10kΩ pull-up ถึง 5V) |
| NC (ขา 3) | — |
| GND (ขา 4) | GND |

### แบบร่างวงจร

```
Arduino UNO
┌─────────────┐          10kΩ
│          5V ├──────────┬──/\/\/──── VCC (ขา 1)
│             │          │
│          D2 ├──────────┤─────────── DATA (ขา 2)
│             │                       NC  (ขา 3) ── ไม่ต่อ
│         GND ├───────────────────── GND (ขา 4)
└─────────────┘
```

---

## 5. หลักการทำงาน

DHT11 ส่งข้อมูล **40 บิต** ต่อการอ่าน 1 ครั้ง

```
[ 8 bit ความชื้น Integer ] [ 8 bit ความชื้น Decimal ]
[ 8 bit อุณหภูมิ Integer ] [ 8 bit อุณหภูมิ Decimal ]
[ 8 bit Checksum ]

Checksum = ผลรวมของ 4 ไบต์แรก (ตรวจสอบความถูกต้อง)
```

---

## 6. Library ที่ใช้ (PlatformIO)

เพิ่มใน `platformio.ini` :

```ini
lib_deps =
    adafruit/DHT sensor library @ ^1.4.6
    adafruit/Adafruit Unified Sensor @ ^1.1.9
```

---

## 7. โค้ดตัวอย่าง

```cpp
#include <Arduino.h>
#include <DHT.h>

#define DHTPIN  2       // DATA ต่อที่ D2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(9600);
    dht.begin();
    Serial.println("=== DHT11 Sensor ===");
}

void loop() {
    float humidity    = dht.readHumidity();
    float temperature = dht.readTemperature();  // หน่วย °C

    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("ERROR: อ่านค่าไม่ได้!");
        delay(2000);
        return;
    }

    Serial.print("อุณหภูมิ : ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("ความชื้น : ");
    Serial.print(humidity);
    Serial.println(" %RH");

    Serial.println("--------------------");
    delay(2000);  // อ่านซ้ำทุก 2 วินาที (DHT11 รองรับสูงสุด 1 ครั้ง/วินาที)
}
```

---

## 8. ผลลัพธ์ Serial Monitor

```
=== DHT11 Sensor ===
อุณหภูมิ : 28.00 °C
ความชื้น : 65.00 %RH
--------------------
อุณหภูมิ : 28.00 °C
ความชื้น : 65.00 %RH
--------------------
```

---

## 9. ข้อควรระวัง

| ปัญหา | สาเหตุ / วิธีแก้ |
|-------|----------------|
| อ่านค่าไม่ได้ (NaN) | ลืมต่อ Pull-up 10kΩ หรือสายหลวม |
| ค่าสั่นไหว | อ่านถี่เกินไป — ใช้ `delay(2000)` ขึ้นไป |
| ความแม่นยำต่ำ | DHT11 มี error ±2°C / ±5%RH ถ้าต้องการแม่นยำกว่าให้ใช้ **DHT22** |
| ย่านวัดจำกัด | DHT11 วัดได้แค่ 0–50°C ถ้าอยู่นอกช่วงนี้ค่าจะผิด |

---

## 10. เปรียบเทียบ DHT11 vs DHT22

| คุณสมบัติ | DHT11 | DHT22 |
|----------|-------|-------|
| ราคา | ถูกกว่า | แพงกว่า |
| ย่านอุณหภูมิ | 0 – 50 °C | -40 – 80 °C |
| ความแม่นยำอุณหภูมิ | ± 2 °C | ± 0.5 °C |
| ย่านความชื้น | 20 – 90 %RH | 0 – 100 %RH |
| ความแม่นยำความชื้น | ± 5 %RH | ± 2 %RH |
| อัตราการอ่าน | 1 ครั้ง/วินาที | 0.5 ครั้ง/วินาที |

---

*อ้างอิง: DHT11 Datasheet, Adafruit DHT Library*
