# Arduino UNO R3 — โครงสร้างบอร์ดและขาใช้งาน

## 1. ภาพรวมบอร์ด Arduino UNO R3

```
                        USB Type-B
                           │
  ┌────────────────────────┴──────────────────────────────┐
  │  [RESET]                                  [PWR LED]   │
  │                                           [TX LED]    │
  │  [ATmega328P]          [ATmega16U2]       [RX LED]    │
  │                        (USB-to-Serial)    [L LED]     │
  │                                                        │
  │  POWER     ┌──────────────────────────────────────┐   │
  │  JACK      │  Digital Pins 0–13 + AREF + GND      │   │
  │   ⊙        └──────────────────────────────────────┘   │
  │            ┌──────────────────────────────────────┐   │
  │            │  Analog Pins A0–A5 + Power Header    │   │
  │            └──────────────────────────────────────┘   │
  └────────────────────────────────────────────────────────┘
```

**Microcontroller:** ATmega328P  
**Clock Speed:** 16 MHz  
**Flash Memory:** 32 KB (0.5 KB used by Bootloader)  
**SRAM:** 2 KB  
**EEPROM:** 1 KB  
**Operating Voltage:** 5V  
**Input Voltage (recommended):** 7–12V  

---

## 2. หัว Power (Power Header)

| ขา | ชื่อ | คำอธิบาย |
|----|------|----------|
| 1 | IOREF | แรงดัน Logic ของบอร์ด (5V) ใช้ให้ Shield รู้ว่าบอร์ดทำงานที่ใด |
| 2 | RESET | ดึงลง GND เพื่อ Reset MCU |
| 3 | 3.3V | แรงดัน 3.3V จาก Regulator (สูงสุด 50 mA) |
| 4 | 5V | แรงดัน 5V regulated (จาก USB หรือ DC Jack) |
| 5 | GND | กราวด์ |
| 6 | GND | กราวด์ (เผื่อไว้) |
| 7 | VIN | แรงดันอินพุตภายนอก (7–12V) เมื่อใช้ DC Jack |

---

## 3. ขา Digital (Digital Pins 0–13)

| ขา | ATmega Pin | ทิศทาง | ฟังก์ชันหลัก | ฟังก์ชันเสริม | Timer / Interrupt |
|----|-----------|--------|-------------|--------------|-------------------|
| **D0** | PD0 | INPUT (default) | RX — รับข้อมูล UART | Digital I/O | — |
| **D1** | PD1 | OUTPUT | TX — ส่งข้อมูล UART | Digital I/O | — |
| **D2** | PD2 | INPUT/OUTPUT | Digital I/O | — | **INT0** (RISING/FALLING/CHANGE) |
| **D3** | PD3 | INPUT/OUTPUT | Digital I/O | **PWM ~** | **INT1** (RISING/FALLING/CHANGE) / Timer2 OC2B |
| **D4** | PD4 | INPUT/OUTPUT | Digital I/O | — | — |
| **D5** | PD5 | INPUT/OUTPUT | Digital I/O | **PWM ~** | Timer0 OC0B |
| **D6** | PD6 | INPUT/OUTPUT | Digital I/O | **PWM ~** | Timer0 OC0A |
| **D7** | PD7 | INPUT/OUTPUT | Digital I/O | — | — |
| **D8** | PB0 | INPUT/OUTPUT | Digital I/O | — | — |
| **D9** | PB1 | INPUT/OUTPUT | Digital I/O | **PWM ~** | Timer1 OC1A |
| **D10** | PB2 | INPUT/OUTPUT | Digital I/O | **PWM ~** / SPI SS | Timer1 OC1B |
| **D11** | PB3 | INPUT/OUTPUT | Digital I/O | **PWM ~** / SPI MOSI | Timer2 OC2A |
| **D12** | PB4 | INPUT/OUTPUT | Digital I/O | SPI MISO | — |
| **D13** | PB5 | INPUT/OUTPUT | Digital I/O | SPI SCK / **LED_BUILTIN** | — |

### ขา PWM ทั้งหมด

| ขา PWM | Timer | Channel | ความถี่ | หมายเหตุ |
|--------|-------|---------|---------|---------|
| D3 | Timer2 | OC2B | **490 Hz** | — |
| D5 | Timer0 | OC0B | **980 Hz** | Timer0 ใช้ร่วมกับ millis()/delay() |
| D6 | Timer0 | OC0A | **980 Hz** | Timer0 ใช้ร่วมกับ millis()/delay() |
| D9 | Timer1 | OC1A | **490 Hz** | Timer1 (16-bit) ปรับความถี่ได้ละเอียด |
| D10 | Timer1 | OC1B | **490 Hz** | Timer1 (16-bit) ปรับความถี่ได้ละเอียด |
| D11 | Timer2 | OC2A | **490 Hz** | — |

> ค่า PWM: 0–255 (8-bit) ใช้ `analogWrite(pin, value)`  
> ระวัง: ขา D5, D6 ใช้ Timer0 ร่วมกับ `millis()` หากเปลี่ยนความถี่จะทำให้ `millis()` คลาดเคลื่อน

### External Interrupt

| ขา | Interrupt | โหมดที่รองรับ |
|----|-----------|--------------|
| D2 | INT0 | LOW, CHANGE, RISING, FALLING |
| D3 | INT1 | LOW, CHANGE, RISING, FALLING |

```cpp
attachInterrupt(digitalPinToInterrupt(2), myISR, FALLING);
```

---

## 4. ขา Analog (Analog Pins A0–A5)

| ขา | ATmega Pin | ADC Channel | ฟังก์ชันเสริม | Digital Pin |
|----|-----------|------------|--------------|-------------|
| **A0** | PC0 | ADC0 | — | D14 |
| **A1** | PC1 | ADC1 | — | D15 |
| **A2** | PC2 | ADC2 | — | D16 |
| **A3** | PC3 | ADC3 | — | D17 |
| **A4** | PC4 | ADC4 | **I2C SDA** | D18 |
| **A5** | PC5 | ADC5 | **I2C SCL** | D19 |

> **ADC:** 10-bit → ค่า 0–1023, อัตราการแปลง ~9.6 kSPS  
> **AREF Pin:** ขาอ้างอิงแรงดัน Analog — ค่าเริ่มต้น = 5V (DEFAULT)

### โหมด Analog Reference

| โหมด | คำสั่ง | แรงดันอ้างอิง |
|------|--------|--------------|
| DEFAULT | `analogReference(DEFAULT)` | 5V (VCC) |
| INTERNAL | `analogReference(INTERNAL)` | 1.1V ภายใน |
| EXTERNAL | `analogReference(EXTERNAL)` | ขา AREF (0–5V) |

```cpp
// ตัวอย่างอ่านค่า Analog และแปลงเป็นแรงดัน
int raw    = analogRead(A0);
float volt = raw * (5.0 / 1023.0);   // DEFAULT reference
float temp = volt * 100.0;           // LM35: 10mV/°C
```

---

## 5. โปรโตคอลสื่อสารบนบอร์ด UNO R3

### UART (Serial)
```
Pin 0 (RX) ←── รับข้อมูล
Pin 1 (TX) ──→ ส่งข้อมูล
```
ใช้งาน: `Serial.begin(9600)`, `Serial.print()`, `Serial.read()`

---

### I2C
```
A4 = SDA  (Data)
A5 = SCL  (Clock)
```
ต้อง pull-up resistor 4.7kΩ ถึง VCC  
Library: `Wire.h`

```cpp
#include <Wire.h>
Wire.begin();
Wire.beginTransmission(0x3C);  // address ของ Slave
Wire.write(data);
Wire.endTransmission();
```

---

### SPI
```
Pin 10 = SS   (Slave Select / Chip Select)
Pin 11 = MOSI (Master Out Slave In)
Pin 12 = MISO (Master In Slave Out)
Pin 13 = SCK  (Clock)
```
Library: `SPI.h`

```cpp
#include <SPI.h>
SPI.begin();
digitalWrite(10, LOW);   // เลือก Slave
SPI.transfer(0xAB);      // ส่งข้อมูล
digitalWrite(10, HIGH);  // ยกเลิกเลือก Slave
```

---

## 6. แผนผังขาทั้งหมด (Pin Map สรุป)

```
                       Arduino UNO R3
             ┌─────────────────────────────┐
             │           [USB]             │
             │                             │
  ┌──────────┤◄ Digital Header ►           │
  │          │                             │
  │   RESET ─┤─ RESET                      │
  │    3.3V ─┤─ 3.3V                       │
  │      5V ─┤─ 5V                         │
  │     GND ─┤─ GND                        │
  │     GND ─┤─ GND                        │
  │     VIN ─┤─ VIN         [DC JACK]      │
  │          │                             │
  │      A0 ─┤─ A0                         │
  │      A1 ─┤─ A1                         │
  │      A2 ─┤─ A2                         │
  │      A3 ─┤─ A3                         │
  │  SDA/A4 ─┤─ A4                         │
  │  SCL/A5 ─┤─ A5                         │
  └──────────┘                             │
                                           │
          ┌────────────────────────────────┤
          │                                │
          │  D0 (RX)  ──────────────────── │
          │  D1 (TX)  ──────────────────── │
          │  D2       ──────────── INT0 ── │
          │  D3  (~)  ──────  INT1/PWM  ── │
          │  D4       ──────────────────── │
          │  D5  (~)  ────────────  PWM ── │
          │  D6  (~)  ────────────  PWM ── │
          │  D7       ──────────────────── │
          │  D8       ──────────────────── │
          │  D9  (~)  ────────────  PWM ── │
          │  D10 (~)  ──────── SS/PWM  ── │
          │  D11 (~)  ────── MOSI/PWM  ── │
          │  D12      ─────────── MISO ── │
          │  D13      ──── SCK/LED(L)  ── │
          │  GND      ──────────────────── │
          │  AREF     ──────────────────── │
          └────────────────────────────────┘
```

### ตำแหน่งหัวต่อบนบอร์ด (จากซ้ายไปขวา)

**Digital Header (บนบอร์ด ด้านบน) — 16 ขา:**
```
[D0][D1][D2][D3][D4][D5][D6][D7][D8][D9][D10][D11][D12][D13][GND][AREF]
 RX  TX      ~           ~   ~           ~    ~    ~    ~
            INT0 INT1
```

**Analog + Power Header (บนบอร์ด ด้านล่าง) — 12 ขา:**
```
[IOREF][RESET][3.3V][5V][GND][GND][VIN]  [A0][A1][A2][A3][A4][A5]
                                              SDA SCL
```

---

## 7. ค่าไฟฟ้าที่ควรรู้

| พารามิเตอร์ | ค่า |
|------------|-----|
| Operating Voltage | 5V |
| กระแสสูงสุดต่อขา Digital | 40 mA (แนะนำ ≤ 20 mA) |
| กระแสรวมสูงสุด (3.3V Pin) | 50 mA |
| กระแสรวมสูงสุด (5V Pin จาก USB) | ~400–500 mA |
| Pull-up Resistor ภายใน | 20–50 kΩ |
| แรงดัน Logic HIGH | ≥ 3.0V |
| แรงดัน Logic LOW | ≤ 1.5V |

---

## 8. ฟังก์ชัน Arduino พื้นฐาน

### Digital I/O
```cpp
pinMode(pin, OUTPUT);        // กำหนดเป็น Output
pinMode(pin, INPUT);         // กำหนดเป็น Input (ลอยได้ถ้าไม่ต่ออะไร)
pinMode(pin, INPUT_PULLUP);  // Input + เปิด Pull-up ภายใน (~47kΩ)

digitalWrite(pin, HIGH);     // ส่งสัญญาณ HIGH (5V)
digitalWrite(pin, LOW);      // ส่งสัญญาณ LOW (0V)
int val = digitalRead(pin);  // อ่านค่า HIGH(1) หรือ LOW(0)
```

### Analog I/O
```cpp
int raw = analogRead(A0);          // อ่าน ADC 10-bit (0–1023)
float volt = raw * (5.0 / 1023.0); // แปลงเป็นแรงดัน (V)

analogWrite(pin, value);           // ออก PWM 8-bit (0–255) เฉพาะขา ~
// value=0 → 0% duty cycle (LOW ตลอด)
// value=127 → ~50% duty cycle
// value=255 → 100% duty cycle (HIGH ตลอด)
```

### Analog Reference
```cpp
analogReference(DEFAULT);   // 5V (VCC) — ค่าเริ่มต้น
analogReference(INTERNAL);  // 1.1V — ใช้กับสัญญาณแรงดันต่ำมาก
analogReference(EXTERNAL);  // ขา AREF — ต่อแรงดันอ้างอิงภายนอก
```

### External Interrupt
```cpp
// โหมด: LOW, CHANGE, RISING, FALLING
attachInterrupt(digitalPinToInterrupt(2), myISR, FALLING);
detachInterrupt(digitalPinToInterrupt(2));

void myISR() {
    // ISR ต้องสั้น ห้าม delay() ภายใน
}
```

### Timing
```cpp
delay(1000);                    // หยุด 1000 ms (บล็อก CPU)
delayMicroseconds(50);          // หยุด 50 µs
unsigned long t = millis();     // เวลาตั้งแต่ reset (ms) — overflow ~49 วัน
unsigned long t = micros();     // เวลา (µs) — overflow ~70 นาที

// Non-blocking timing pattern
unsigned long prev = 0;
const long interval = 1000;

void loop() {
    unsigned long now = millis();
    if (now - prev >= interval) {
        prev = now;
        // ทำงานทุก 1 วินาทีโดยไม่บล็อก
    }
}
```

---

## 9. ข้อควรระวัง

| ข้อควรระวัง | รายละเอียด |
|------------|------------|
| กระแสเกิน | แต่ละขา Digital ห้ามเกิน **40 mA** — LED ต้องใช้ Resistor |
| แรงดัน 3.3V | ขา I/O ของ UNO เป็น **5V Logic** ต่อกับ Module 3.3V ต้องใช้ Level Converter |
| Pin 0, 1 | ใช้ Serial Upload — ห้ามต่ออุปกรณ์ขณะ Upload โปรแกรม |
| Pin 13 | มี LED และ Resistor ต่ออยู่แล้ว ระวังการใช้เป็น Input |
| Analog Reference | ถ้าต่อขา AREF ต้องเรียก `analogReference(EXTERNAL)` ก่อนอ่าน |

---

*อ้างอิง: Arduino UNO R3 Datasheet, ATmega328P Datasheet, arduino.cc/en/Main/ArduinoBoardUno*
