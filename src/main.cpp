#include <Arduino.h>

#define LED_PIN     13    // Built-in LED (D13)
#define BLINK_MS    500   // กระพริบทุก 500 ms

unsigned long prevTime = 0;
bool ledState = LOW;

void setup() {
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);
    Serial.println("Blink Test Start");
}

void loop() {
    unsigned long now = millis();

    if (now - prevTime >= BLINK_MS) {
        prevTime = now;
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState);
        Serial.print("LED: ");
        Serial.println(ledState ? "ON" : "OFF");
    }
}
