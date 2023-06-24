#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Keypad.h>

// keypad configuration
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
LiquidCrystal_I2C lcd(0x27, 16, 2);

int ledPins[] = {A3,A2,A1,A0,10}; // pins for the LEDs
int numLeds = sizeof(ledPins) / sizeof(ledPins[0]);
int ledDelay = 100; // delay between LED shifts

const int buzzerPin = 11; // pin for the buzzer

const String password = "*1234"; // the correct password
const int maxAttempts = 3; // maximum number of password attempts
String name = "";

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  // lcd initialization
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.home(); // cursor to home
}

void loop() {
  String enteredPassword = "";
  int attempts = 0;  
  Serial.println();
  Serial.println("Please enter the password:");
  lcd.clear();
  lcd.home(); 
  // lcd.print("enter password:");
  lcd.print("ENTER YOUR NAME:");
  lcd.setCursor(0, 1);
  while (name.length() < 7) {
    char nameLetter = keypad.getKey();
    if (nameLetter) {
      lcd.write(nameLetter);
      name += nameLetter;
    }
  }
  lcd.clear();
  lcd.home();
  lcd.print("Press '*'");

  while (attempts < maxAttempts) {
    char key = keypad.getKey();

    if (key) {
      lcd.clear();
      lcd.home(); 
      lcd.print("enter password:");
      if (key == '#') {
        if (enteredPassword == password) {
          playSuccessTone();
          lightRunningPattern();
          Serial.println("Access granted!");
          lcd.clear();
          lcd.home();
          lcd.print("WELCOME, ");
          lcd.setCursor(0,1);
          lcd.print(name);
          delay(10000);
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
          lcd.clear();
          lcd.home();
          lcd.print("ATTEMPTS LEFT: ");
          // lcd.setCursor(14,0);
          lcd.print(maxAttempts - attempts);
          // lcd.print(attempts);
          // lcd.print(" ATEMPT ALREADY");
          lcd.setCursor(0, 1);
          lcd.print("Press '*'");
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
    Serial.println("You can try again after 10 seconds.");
    lcd.clear();
    lcd.home();
    lcd.print("ACCESS DENIED!!!");
    lcd.setCursor(0, 1);
    lcd.print("Try again later");
    delay(10000);
    Serial.println("You can try again:");
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