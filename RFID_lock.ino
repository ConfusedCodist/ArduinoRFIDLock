#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <RFID.h>
#include <Servo.h>
#include <Wire.h>

#define SDA_DIO 9
#define RESET_DIO 8

RFID RC522(SDA_DIO, RESET_DIO);
Servo Servo1;

int servoPin = 7;
LiquidCrystal_I2C lcd(0x3F, 16, 2);
void setup() {
  lcd.setCursor(2, 0);
  lcd.print("Scan");
  lcd.setCursor(2, 1);
  lcd.print("Card.");


  lcd.init();
  lcd.clear();
  lcd.backlight();
  Servo1.attach(servoPin);
  Serial.begin(9600);

  SPI.begin();

  RC522.init();
}

void loop() {



  Servo1.write(90);

  if (RC522.isCard()) {

    RC522.readCardSerial();
    Serial.println("Card detected:");
    for (int i = 0; i < 5; i++) {
      Serial.print(RC522.serNum[i], DEC);
      Serial.print(" : ");
    }
    Serial.println();
    Serial.println();
  }
  delay(1000);
  // if tag = 671151071485 then turn servo 180 degrese
  if (RC522.serNum == 671151071485) {
    lcd.setCursor(2, 0);
    lcd.print("Access");
    lcd.setCursor(2, 1);
    lcd.print("Granted");
    Servo1.write(180);
    delay(5000);
  }
}