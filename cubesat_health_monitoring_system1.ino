#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define TEMP A0
#define LIGHT A1
#define BAT A2

#define EMERGENCY 2
#define SAFE 3
#define GREEN 8
#define YELLOW 9
#define RED 10
#define BUZZER 11

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(EMERGENCY, INPUT_PULLUP);
  pinMode(SAFE, INPUT_PULLUP);
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  lcd.print("CUBESAT SYSTEM");
  delay(1500);
  lcd.clear();
}

void loop() {
  float temp = analogRead(TEMP) * 5.0 / 1023 * 100 - 50;
  int light = analogRead(LIGHT) * 100 / 1023;
  float bat = analogRead(BAT) * 5.0 / 1023;

  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temp, 0);
  lcd.print("C B:");
  lcd.print(bat, 1);
  lcd.print("V ");

  lcd.setCursor(0, 1);

  if (digitalRead(EMERGENCY) == LOW) {
    lcd.print("!!! EMERGENCY !!!");
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, LOW);
    digitalWrite(YELLOW, LOW);
    tone(BUZZER, 1000);
  }
  else if (digitalRead(SAFE) == LOW || temp > 60 || bat < 3.3) {
    lcd.print("SAFE MODE       ");
    digitalWrite(YELLOW, HIGH);
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, LOW);
    tone(BUZZER, 500);
  }
  else {
    lcd.print("NORMAL L:");
    lcd.print(light);
    lcd.print("%   ");
    digitalWrite(GREEN, HIGH);
    digitalWrite(YELLOW, LOW);
    digitalWrite(RED, LOW);
    noTone(BUZZER);
  }

  delay(500);
}