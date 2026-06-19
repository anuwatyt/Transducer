# รหัส 000000000 นาย อนุวัฒน์ สุชาโต
## แผนกเทคนิคคอมพิวเตอร์

# LAB2 Blynk2LED
ต่อ LED 2 ตัวให้กระพริบสลับกันบน Arduino UNO

---

## อุปกรณ์
| อุปกรณ์ | จำนวน |
|---------|:-----:|
| Arduino UNO | 1 |
| LED | 2 |
| ตัวต้านทาน 220Ω | 2 |

---

## การต่อวงจร
| LED | Pin | GND |
|-----|-----|-----|
| LED1 | D12 | ผ่าน 220Ω |
| LED2 | D13 | ผ่าน 220Ω |

### แบบร่างวงจร

```
   Arduino UNO
  ┌─────────────┐
  │          D12├────[220Ω]────┤▶├──── GND
  │             │               LED1
  │          D13├────[220Ω]────┤▶├──── GND
  │             │               LED2
  │         GND├──────────────────────── GND
  └─────────────┘
```

### แบบร่าง Breadboard

```
Arduino UNO                Breadboard
                        +──────────────────+
  D12 ──────────────────┤ a1               │
                        │  [220Ω] b1─c1    │
                        │         ┤▶├ d1   │  ← LED1
                        │              e1──┤── GND rail
  D13 ──────────────────┤ a2               │
                        │  [220Ω] b2─c2    │
                        │         ┤▶├ d2   │  ← LED2
                        │              e2──┤── GND rail
  GND ─────────────────────────────────────┤── GND rail
                        +──────────────────+
```

---

## โค้ด

```cpp
#include <Arduino.h>

#define LED1_PIN  12
#define LED2_PIN  13
#define BLINK_MS  500

unsigned long prevTime = 0;
bool ledState = false;

void setup() {
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);
}

void loop() {
    if (millis() - prevTime >= BLINK_MS) {
        prevTime = millis();
        ledState = !ledState;
        digitalWrite(LED1_PIN, ledState);
        digitalWrite(LED2_PIN, !ledState);
    }
}
```

---

## ผลลัพธ์
LED1 และ LED2 กระพริบสลับกันทุก **500 ms**
- LED1 ติด → LED2 ดับ
- LED1 ดับ → LED2 ติด
