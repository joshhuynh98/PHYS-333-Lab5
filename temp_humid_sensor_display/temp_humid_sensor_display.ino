#include "Adafruit_Si7021.h"
#include <Wire.h>
#define trigPin 7
#define echoPin 4
#include <LiquidCrystal.h>

const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Adafruit_Si7021 sensor = Adafruit_Si7021();

boolean isTemp;

float maxTemp = 0;
float minTemp = 100;

float maxHum = 0;
float minHum = 100;

long t0;

void setup() {
  Serial.begin(9600);

  // wait for serial port to open
  while (!Serial) {
    delay(10);
  }

  Serial.println("Si7021 test!");

  sensor.begin();
  
  if (!sensor.begin()) {
    Serial.println("Did not find Si7021 sensor!");
    while (true);
  }

  lcd.begin(16, 2);
  lcd.print("in setup");

  // initial states
  t0 = millis();
  isTemp = true;
}

void loop() {
  float temp = sensor.readTemperature();
  float hum = sensor.readHumidity();

  // check min, max
  if (temp<minTemp) minTemp = temp;
  if (temp>maxTemp) maxTemp = temp;

  if (hum<minHum) minHum = hum;
  if (hum>maxHum) maxHum = hum;

  // display temp for 4s, then humidity for 4s
  if ((millis() - t0) > 4000) {
    isTemp = !isTemp;
    t0 = millis();
  }
  
  lcd.clear();
  
  if (isTemp) {
    lcd.setCursor(0,0);
    lcd.print("Temp");
    lcd.setCursor(6,0);
    lcd.print("Min");
    lcd.setCursor(11,0);
    lcd.print("Max");

    lcd.setCursor(0,1);
    lcd.print(temp,2);
    lcd.setCursor(6,1);
    lcd.print(minTemp,1);
    lcd.setCursor(11,1);
    lcd.print(maxTemp,1);
  }
  else {
    lcd.setCursor(0,0);
    lcd.print("Humid");
    lcd.setCursor(6,0);
    lcd.print("Min");
    lcd.setCursor(11,0);
    lcd.print("Max");

    lcd.setCursor(0,1);
    lcd.print(hum,2);
    lcd.setCursor(6,1);
    lcd.print(minHum,1);
    lcd.setCursor(11,1);
    lcd.print(maxHum,1);
  }

  Serial.print(millis() / 1000);
  Serial.print("\t"); Serial.print(hum, 2);
  Serial.print("\t"); Serial.println(temp, 2);
  delay(1000);
}
