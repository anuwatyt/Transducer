#include <Arduino.h>
#include <Wire.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

// DHT11: ขา DATA => D4 (PD4 — Digital I/O)
// ต่อ Pull-up 10kΩ ระหว่างขา DATA กับ VCC
#define DHTPIN   4
#define DHTTYPE  DHT11

// LCD 16x2 I2C: SDA => A4, SCL => A5, address 0x27
#define LCD_ADDR 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

void setup() {
    Serial.begin(9600);
    dht.begin();

    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("DHT11 Sensor");
    lcd.setCursor(0, 1);
    lcd.print("UNO R3 - D4");

    Serial.println("============================");
    Serial.println("   DHT11 Sensor - UNO R3   ");
    Serial.println("   DATA => D4 (PD4)        ");
    Serial.println("   LCD I2C => 0x27         ");
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

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Sensor Error");
        lcd.setCursor(0, 1);
        lcd.print("Check DHT11");
        return;
    }

    Serial.print("อุณหภูมิ : ");
    Serial.print(temperature, 1);
    Serial.println(" C");

    Serial.print("ความชื้น : ");
    Serial.print(humidity, 1);
    Serial.println(" %RH");

    Serial.println("----------------------------");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature, 1);
    lcd.print((char)223);
    lcd.print("C");

    lcd.setCursor(0, 1);
    lcd.print("Hum : ");
    lcd.print(humidity, 1);
    lcd.print(" %");
}
