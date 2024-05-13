#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte ROWS = 4;  // four rows
const byte COLS = 4;  // four columns

// Map the buttons to an array for the Keymap instance
char hexaKeys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

byte colPins[ROWS] = { 5, 4, 3, 2 };  // Pins used for the rows of the keypad
byte rowPins[COLS] = { 9, 8, 7, 6 };  // Pins used for the columns of the keypad

// Initialise the Keypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

int buzzer_pin = 10;
int green_light = 11;
int red_light = 12;
char cor_seq[5] = { '1', '2', '3', '4', 'A' };
char pressedKey[5];
int i = 0;

void setup() {
  pinMode(buzzer_pin, OUTPUT);
  pinMode(green_light, OUTPUT);
  pinMode(red_light, OUTPUT);
  
  //initialize lcd screen
  lcd.init();
  // turn on the backlight
  lcd.backlight();
}

int cheak(char a[], char b[]) {
  for (int j = 0; j < 5; j++) {
    if (a[j] != b[j]) return 0;
  }
  return 1;
}

void loop() {
  char key = customKeypad.getKey();
  if (key) {
    pressedKey[i] = key;
    lcd.print(pressedKey[i]);
    i++;
    if (key == 'A') {
      if (cheak(cor_seq, pressedKey) == 0) {
        lcd.clear();
        lcd.print("Wrong Password");
        digitalWrite(red_light, HIGH);
        delay(3000);
        digitalWrite(red_light, LOW);
      } else {
        lcd.clear();
        lcd.print("Access Granted");
        digitalWrite(green_light, HIGH);
        delay(3000);
        digitalWrite(green_light, LOW);
      }
    }
  }
}
