

#include <LiquidCrystal_I2C.h>
#include <string.h>
#include <Wire.h>
#include <Keypad.h>


char pressedKey;
int buzzer_pin = 10;
int green_light = 11;
int red_light = 12;

const byte ROWS = 4;  // four rows
const byte COLS = 4;  // four columns
String desiredString = "1234A";

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


//initialize the liquid crystal library
//the first parameter is  the I2C address
//the second parameter is how many rows are on your screen
//the  third parameter is how many columns are on your screen
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(buzzer_pin, OUTPUT);
  pinMode(green_light, OUTPUT);
  pinMode(red_light, OUTPUT);

  //initialize lcd screen
  lcd.init();
  // turn on the backlight
  lcd.backlight();
  Serial.begin(9600);  // Initialize serial communication for debugging (optional)
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

  char key = customKeypad.getKey();

  if (key) {
    lcd.print(key);  // Print the pressed key to the serial monitor (optional)

    // Check if the pressed key matches the desired string character by character
    if (String(key) == desiredString.substring(0, 1)) {
      desiredString = desiredString.substring(1);  // Remove the matched character

      if (desiredString.length() == 0) {
        // The entire desired string was pressed - perform your action here!
        lcd.clear();
        lcd.print("Access Granted");
        digitalWrite(green_light, HIGH);
        delay(3000);
        digitalWrite(green_light, LOW);
      }

    } else {
      // Reset the desired string if the sequence is broken
      desiredString = "1234A";
      digitalWrite(red_light, HIGH);
      delay(1000);
      digitalWrite(red_light, LOW);
    }
  }
}
