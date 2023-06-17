#include <Keypad.h>

const byte ROWS = 4; // number of rows on the keypad
const byte COLS = 4; // number of columns on the keypad

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};     // connect to the row pinouts of the keypad
byte colPins[COLS] = {2,3,4,5};     // connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


int ledPins[] = {10, 11, 12, 13, A1}; // pins for the LEDs
int numLeds = sizeof(ledPins) / sizeof(ledPins[0]);
int ledDelay = 100; // delay between LED shifts

const int buzzerPin = A0; // pin for the buzzer

const String password = "1234"; // the correct password
const int maxAttempts = 3; // maximum number of password attempts

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  String enteredPassword = "";
  int attempts = 0;  
  Serial.println();
  Serial.println("Please enter the password:");

  while (attempts < maxAttempts) {
    char key = keypad.getKey();

    if (key) {
      if (key == '#') {
        if (enteredPassword == password) {
          playSuccessTone();
          lightRunningPattern();
          Serial.println("Access granted!");
          break;
        } else {
          playErrorTone();
          lightErrorPattern();
          lightErrorPattern();
          lightErrorPattern();
          enteredPassword = "";
          attempts++;
          Serial.print("Numbers of attempt left: ");
          Serial.println(maxAttempts - attempts);          
        }
      } else {
        enteredPassword += key;
        Serial.println(enteredPassword);
        Serial.println("Press '#' to check the entered password.");    
      }
    }
  }

  if (attempts >= maxAttempts) {
    keypad.setDebounceTime(0);
    keypad.setHoldTime(0);
    // keypad.setSingleKeyTimeout(0);
    keypad.addEventListener(NULL);
    Serial.println("Access denied!");
    Serial.println("You can try again after 30 seconds.");
    delay(10000);
    Serial.println("You can try again:");
  }

  // Disable further keypad input if max attempts exceeded
  while (true) {
    // Do nothing
  }
}


void playSuccessTone() {
  tone(buzzerPin, 1000, 500);
  delay(500);
  tone(buzzerPin, 1100, 500);
  delay(500);
  tone(buzzerPin, 1200, 500);
  delay(500);
}

void playErrorTone() {
  tone(buzzerPin, 300, 1000);
  delay(500);
  tone(buzzerPin, 250, 1000);
  delay(500);
  tone(buzzerPin, 200, 1000);
  delay(500);
}

void lightRunningPattern() {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], HIGH);
    delay(ledDelay);
  }
  delay(5000);
  for (int i = numLeds - 1; i >= 0; i--) {
    digitalWrite(ledPins[i], LOW);
    delay(ledDelay);
  }
}

void lightErrorPattern() {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
  delay(ledDelay);
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  delay(ledDelay);
}