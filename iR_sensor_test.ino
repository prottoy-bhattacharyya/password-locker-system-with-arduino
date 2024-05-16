#include <LiquidCrystal_I2C.h>
#include <Servo.h>

void open();
void close();

int servoPin = 5;
Servo s;
LiquidCrystal_I2C lcd(0x27, 16, 2);

int IRSensor = 9;
void close() {
  s.write(0);
}

void open() {
  s.write(180);
}

void setup() {
  pinMode(IRSensor, INPUT);
  lcd.init();
  lcd.backlight();
  s.attach(servoPin);
  s.write(0);
}

void loop() {
  if (digitalRead(IRSensor) == 0) {
    lcd.clear();
    lcd.print("Motion Detected");
    open();
    delay(2000);
  }

  else {
    lcd.clear();
    lcd.print("No Motion");
    close();
  }
}
