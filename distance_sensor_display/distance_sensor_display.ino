#define trigPin 7
#define echoPin 4
#include <LiquidCrystal.h>

const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

float old_distance=0;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);

  lcd.begin(16, 2);
  lcd.print("in setup");
}

void loop() {
  long pulse_length_us;
  float distance_m;
  float avg_distance=0;
  float avg_velocity=0;
  
  for (int i=0; i<5; i++) {
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
  
    pulse_length_us = pulseIn(echoPin, HIGH);
    distance_m = (float) pulse_length_us * 0.000170;
  
    avg_velocity += (distance_m - old_distance);
    avg_distance += distance_m;
    old_distance = distance_m;
    
    delay(200);
  }
  avg_distance /= 5;
  
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print(avg_distance);
  lcd.setCursor(6,0);
  lcd.print("meters");
  
  lcd.setCursor(0,1);
  lcd.print(avg_velocity);
  lcd.setCursor(6,1);
  lcd.print("m/s");

  Serial.print(millis() / 1000); Serial.print("\t");
  Serial.print(avg_distance); Serial.print("(m)\n");
}
