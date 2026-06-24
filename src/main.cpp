#include <Arduino.h>

#define REED_PIN   2
#define LED_PIN    13
#define BAUD_RATE  9600
#define SAMPLE_MS  200

unsigned long prevTime = 0;

void setup() {
    Serial.begin(BAUD_RATE);
    pinMode(REED_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    Serial.println("KY-021 test started");
    Serial.println("Use magnet near the sensor and watch Serial Monitor");
}

void loop() {
    unsigned long now = millis();

    if (now - prevTime >= SAMPLE_MS) {
        prevTime = now;

        int state = digitalRead(REED_PIN);

        if (state == LOW) {
            digitalWrite(LED_PIN, HIGH);
            Serial.println("Magnet detected");
        } else {
            digitalWrite(LED_PIN, LOW);
            Serial.println("No magnet");
        }
    }
}
