

#include <LiquidCrystal_I2C.h>

#include  <Wire.h>
#include <Keypad.h>

const byte ROWS = 4; // four rows
const byte COLS = 4; // four columns

// Map the buttons to an array for the Keymap instance
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte colPins[ROWS] = {5, 4, 3, 2}; // Pins used for the rows of the keypad
byte rowPins[COLS] = {9, 8, 7, 6}; // Pins used for the columns of the keypad

// Initialise the Keypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);


//initialize the liquid crystal library
//the first parameter is  the I2C address
//the second parameter is how many rows are on your screen
//the  third parameter is how many columns are on your screen
LiquidCrystal_I2C lcd(0x27,  16, 2);
char pressedKey;

void setup() {
  
  //initialize lcd screen
  lcd.init();
  // turn on the backlight
  lcd.backlight();
}
// void loop() {
// //  // wait  for a second
// //   delay(1000);
// //   // tell the screen to write on the top row
// //   lcd.setCursor(0,0);
// //   // tell the screen to write “hello, from” on the top  row
// //   lcd.print("hello");
// //   // tell the screen to write on the bottom  row
// //   lcd.setCursor(0,1);
// //   // tell the screen to write “Arduino_uno_guy”  on the bottom row
// //   // you can change whats in the quotes to be what you want  it to be!
// //   lcd.print("world");
//   char button = customKeypad.getKey();
//   if (button) { 
   
//     lcd.print(button);
//   }
// }
void loop() {
  pressedKey = customKeypad.getKey();

  if (pressedKey) {
    if (pressedKey == 'B') {
      lcd.clear();
    } else {
      lcd.print(pressedKey);
    }
  }
}
