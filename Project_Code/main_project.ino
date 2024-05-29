#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
// GND-> ground
// VCC-> +5V
// SDA-> A4
// SCL-> A5

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

byte colPins[ROWS] = { 5, 4, 3, 2 };
byte rowPins[COLS] = { 9, 8, 7, 6 };

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

Servo s1;
int servo_pin = 10;
int green_light = 11;
int red_light = 12;
int buzzer_pin = 12;

char cor_seq[5] = { '1', '5', '8', '3', 'D' };  //password= "1583" press D to enter
char pressedKey[5];
int i = 0;

void (*resetFunc)(void) = 0;  //reset function

int cheak(char a[], char b[]) {
  for (int j = 0; j < 5; j++) {
    if (a[j] != b[j]) return 0;
  }
  return 1;
}

void on_off(int pin1) {
  if(pin1 == green_light) {
    lcd.clear();
    lcd.print("Processing...");
    
  }
  for (int j = 0; j < 5; j++) {
      digitalWrite(pin1, HIGH);
      delay(300);
      digitalWrite(pin1, LOW);
      delay(300);
    }
}

void openGate() {
  lcd.clear();
  lcd.print("Opening Gate...");
  s1.write(100);
  delay(6000);
  s1.write(91);
}

void closeGate() {
  lcd.clear();
  lcd.print("Closing Gate...");
  s1.write(88);
  delay(5000);
  s1.write(91);

  // lcd.print("press c to close");
  // delay(15);
  // if(customKeypad.getKey() == 'C') {
  //   lcd.print("Closing Gate...");
  //   s1.write(88);
  //   delay(5000);
  //   s1.write(91);
  //   return;
  // }
  // else closeGate();
}

void countDown(){
  for(int j=15; j >=0; j--){
	lcd.clear(); 
    lcd.print(j);
    lcd.print("  seconds");
    delay(1000);
  }
}


void setup() {
  s1.attach(servo_pin);
  pinMode(green_light, OUTPUT);
  pinMode(red_light, OUTPUT);
  
  s1.write(91);

  lcd.init();
  lcd.backlight();
  lcd.print("Enter Password: ");
  lcd.setCursor(2, 1);
}


void loop() {

  char key = customKeypad.getKey();
  if (key) {
    pressedKey[i] = key;
    lcd.print("* ");
    // lcd.print(key);
    i++;

    if (key == 'D') {

      if (cheak(cor_seq, pressedKey) == 0) {
        lcd.clear();
        lcd.print("Wrong Password");
        on_off(red_light);
        resetFunc();
      } 
      
      else {
        lcd.clear();
        lcd.print("Access Granted");
        delay(3000);
        on_off(green_light);
        openGate();
        delay(500);
        countDown();
        closeGate();
        resetFunc();
      }
    }
    if (key == 'C') {
      resetFunc();
    }
  }
}
