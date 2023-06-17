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
byte colPins[COLS] = {2, 3, 4, 5};    // Connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String stringInput1 = ""; // Variable to store the first operand
String stringInput2 = ""; // Variable to store the second operand

int ctr; // counter used when entering inputs using '#'
char operand; // for selecting mathematical operator

void setup() {
  Serial.begin(9600); // Set the baud rate for the Serial Monitor
}

void loop() {
  ctr = 0; // counter
  Serial.println();
  Serial.println("Enter your first num then press '#'");
  Serial.println("Enter your second num then press '#'");
  Serial.println("Press '#' to start.");
  while (ctr < 5){
    calculator();
  }
}

long hexToDec(String value){
  long decimal = strtol(value.c_str(), NULL, 16);
  return decimal;
}

long operation(long value1, long value2, char choice){
  long result;
  switch (choice) {
      case 'A':
        result = value1 + value2;
        break;
      case 'B':
        result = value1 - value2;
        break;
      case 'C':
        result = value1 * value2;
        break;
      case 'D':
        result = value1 / value2;
        break;
    }
    return result;
}

void guide(){
  Serial.println("Select an operation to be used:");
  Serial.println("'A' - addition");
  Serial.println("'B' - subtraction");
  Serial.println("'C' - multiplication");
  Serial.println("'D' - division");
}

int calculator(){
  char key = keypad.getKey();

  if (key != NO_KEY) {
    if (key == '#'){
      ctr += 1;

      if (ctr == 1){
        Serial.println();
        Serial.print("First input: ");
      }
      else if (ctr == 2){
        Serial.println();
        Serial.print("Second input: ");
      }
      else if (ctr == 3){
        Serial.println();
        Serial.println();
        guide();
      }

      else if (ctr == 4){
        if ((operand == 'A') || (operand == 'B') || (operand == 'C') || (operand == 'D')){
          if ((operand == 'D') && (hexToDec(stringInput2) == 0)){
            Serial.println("Error: Division by zero!");
          } else {
            char choice = operand;
            int answer = operation(hexToDec(stringInput1), hexToDec(stringInput2), choice);
            Serial.print("Answer in decimals: ");
            Serial.println(answer);
            Serial.println();
          }
          
          // reset variable values
          ctr = 5;
          stringInput1 = "";
          stringInput2 = "";
        }
      }
    }

    else{
      if (ctr == 1){
        stringInput1 += key;
        Serial.print(key);
      } else if (ctr == 2) {
        stringInput2 += key;
        Serial.print(key);
      } else if (ctr == 3) {
        operand = key;
        Serial.print("You chose: ");
        Serial.println(operand);
      }
    }
  }
}