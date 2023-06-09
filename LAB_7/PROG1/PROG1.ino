#include <Keypad.h>

const byte ROWS = 4; // Number of rows on the keypad
const byte COLS = 4; // Number of columns on the keypad

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};    // Connect to the row pinouts of the keypad
byte colPins[COLS] = {2,3,4,5};    // Connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600); // Set the baud rate for the Serial Monitor

}

void loop() {
  char key = keypad.getKey();

  if (key){
    Serial.println(key);
  }
}