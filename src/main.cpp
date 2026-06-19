#include <Arduino.h>
#include <DHT.h>

// DHT11: ขา DATA => D4 (PD4 — Digital I/O)
// ต่อ Pull-up 10kΩ ระหว่างขา DATA กับ VCC
#define DHTPIN   4
#define DHTTYPE  DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(9600);
    dht.begin();
    Serial.println("============================");
    Serial.println("   DHT11 Sensor - UNO R3   ");
    Serial.println("   DATA => D4 (PD4)        ");
    Serial.println("============================");
}

void loop() {
    // DHT11 รองรับการอ่านสูงสุด 1 ครั้ง/วินาที
    delay(2000);

    float humidity    = dht.readHumidity();
    float temperature = dht.readTemperature();  // หน่วย °C

    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("ERROR: อ่านค่าจาก DHT11 ไม่ได้");
        Serial.println(">> ตรวจสอบสาย DATA และ Pull-up 10kΩ");
        return;
    }

    Serial.print("อุณหภูมิ : ");
    Serial.print(temperature, 1);
    Serial.println(" °C");

    Serial.print("ความชื้น : ");
    Serial.print(humidity, 1);
    Serial.println(" %RH");

    Serial.println("----------------------------");
}
