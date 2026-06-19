#include <Arduino.h>

// LED1 => D12 (PB4 — Digital I/O)
// LED2 => D13 (PB5 — Digital I/O / LED_BUILTIN)
// ต่อ Resistor 220Ω อนุกรมทุกตัว (กระแส ≤ 20 mA ต่อขา)

#define LED1_PIN   12
#define LED2_PIN   13
#define BLINK_MS   500   // กระพริบสลับทุก 500 ms

unsigned long prevTime = 0;
bool ledState = false;

void setup() {
    Serial.begin(9600);
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);

    // สถานะเริ่มต้น: LED1 ติด, LED2 ดับ
    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED2_PIN, LOW);

    Serial.println("=== Blink 2 LED ===");
    Serial.println("LED1 => D12 | LED2 => D13");
}

void loop() {
    // Non-blocking timing (ไม่ใช้ delay)
    unsigned long now = millis();
    if (now - prevTime >= BLINK_MS) {
        prevTime = now;
        ledState = !ledState;

        // LED1 และ LED2 กระพริบสลับกัน
        digitalWrite(LED1_PIN,  ledState);
        digitalWrite(LED2_PIN, !ledState);

        Serial.print("LED1: ");
        Serial.print(ledState ? "ON " : "OFF");
        Serial.print("  |  LED2: ");
        Serial.println(ledState ? "OFF" : "ON ");
    }
}
