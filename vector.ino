#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <StandardCplusplus.h>
#include <vector>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

byte colPins[ROWS] = { 5, 4, 3, 2 };
byte rowPins[COLS] = { 9, 8, 7, 6 };  // Pins used for the columns of the keypad

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

vector<char> pressed_key;
vector<char> cor_seq{'1','2','3','4','D'};
int i=0;

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();

}

int cheak(Vector<char> a, Vector<char> b) {
  for (int j = 0; j < 5; j++) {
    if (a[j] != b[j]) return 0;
  return 1;
  }
  
void loop() {
  // put your main code here, to run repeatedly:
  char key=customKeypad.getKey();
  if(key){
    pressed_key[i] = key;
    lcd.print(pressed_key[i]);
    i++;
   if (key == 'D') {

      if (cheak(cor_seq, pressed_key) == 0) {
        
        pressed_key.clear();
        lcd.print("Wrong Password");
        digitalWrite(red_light, HIGH);
        delay(3000);
        digitalWrite(red_light, LOW);
        lcd.clear();
        loop();
      }

      else {
        lcd.clear();
        lcd.print("Access Granted");
        digitalWrite(green_light, HIGH);
        delay(3000);
        digitalWrite(green_light, LOW);
      }
    }
  }
}
