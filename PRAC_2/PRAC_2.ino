// LIBRARY FOR KEYPAD
#include <Keypad.h>
const byte ROWS = 4; // Number of rows on the keypad
const byte COLS = 4; // Number of columns on the keypad
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 10, 11, 12};    // Connect to the row pinouts of the keypad
byte colPins[COLS] = {A3, A2, A1, A0};    // Connect to the column pinouts of the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// LIBRARY FOR LCD I2C
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display


// TOGGLE SWITCH IF UP OR DOWN
int toggle = A5, i = 0; 

//for switch debounce
int reading;
int current_state = LOW;
int debounceDelay = 10;
long lastDebounceTime = 0;
int toggleState = 0;
int current_fromVal = 0;

int arrayName[10] = {0,1,2,3,4,5,6,7,8,9};
int pin1, pin2, pin3;

byte seven_seg_digits[10][7] = { 
  { 1,1,1,1,1,1,0 },  // = 0
  { 0,1,1,0,0,0,0 },  // = 1
  { 1,1,0,1,1,0,1 },  // = 2
  { 1,1,1,1,0,0,1 },  // = 3
  { 0,1,1,0,0,1,1 },  // = 4
  { 1,0,1,1,0,1,1 },  // = 5
  { 1,0,1,1,1,1,1 },  // = 6
  { 1,1,1,0,0,0,0 },  // = 7
  { 1,1,1,1,1,1,1 },  // = 8
  { 1,1,1,0,0,1,1 }   // = 9
};


int cycleCounter = 0;// LIBRARY FOR KEYPAD
#include <Keypad.h>
const byte ROWS = 4; // Number of rows on the keypad
const byte COLS = 4; // Number of columns on the keypad
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 10, 11, 12};    // Connect to the row pinouts of the keypad
byte colPins[COLS] = {A3, A2, A1, A0};    // Connect to the column pinouts of the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// LIBRARY FOR LCD I2C
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// LIBRARY FOR 4 7 SEGMENT
#include "SevSegShift.h"
#define SHIFT_PIN_SHCP 6
#define SHIFT_PIN_STCP 7
#define SHIFT_PIN_DS   8



// TOGGLE SWITCH IF UP OR DOWN
int toggle = A5, i = 0; 

//for switch debounce
int reading;
int current_state = LOW;
int debounceDelay = 10;
long lastDebounceTime = 0;
int toggleState = 0;
int current_fromVal = 0;

int array[10] = {0,1,2,3,4,5,6,7,8,9};
int pin1, pin2, pin3;

byte seven_seg_digits[10][7] = { 
  { 1,1,1,1,1,1,0 },  // = 0
  { 0,1,1,0,0,0,0 },  // = 1
  { 1,1,0,1,1,0,1 },  // = 2
  { 1,1,1,1,0,0,1 },  // = 3
  { 0,1,1,0,0,1,1 },  // = 4
  { 1,0,1,1,0,1,1 },  // = 5
  { 1,0,1,1,1,1,1 },  // = 6
  { 1,1,1,0,0,0,0 },  // = 7
  { 1,1,1,1,1,1,1 },  // = 8
  { 1,1,1,0,0,1,1 }   // = 9
};


int cycleCounter = 0;


void setup() {  
  Serial.begin(9600);


  // FOR SEVEN SEGMENT PINMODE              
  for (int j = 2; j < 9; j++){
    pinMode(j, OUTPUT);
  }
  // FOR INPUT SWITCHES
  for (int j = 9; j < 14; j++){
    digitalWrite(j, INPUT); 
  }

  for (int j = 2; j < 9; j++){
    digitalWrite(j, current_state);
  } 
}




void loop() { 

  lcd.init();
  lcd.backlight();
  lcd.clear();

  lcd.print("STARTING COUNT");
  lcd.home();

  int fromVal;

  char key = keypad.getKey();
  if (key){
    Serial.println(key);

    lcd.setCursor(0, 1);
    lcd.print(key);
    fromVal = lcd.write(key);
    // seven_segment_digits[choice][7];
  }






  //READ ALL SWITCH AND PINS
  // pin1 = digitalRead(10); //most significant bit
  // pin2 = digitalRead(11);
  // pin3 = digitalRead(12); //least significant bit
  reading = digitalRead(toggle);
  //CONVERT DPST READING TO DECIMAL VALUE
  // int fromVal = binToDec(pin1, pin2, pin3); 
  
  if ((reading != current_state) || (fromVal != current_fromVal)){ //ANY CHANGE IN STATE
    lastDebounceTime = millis();
    toggleState = 1;
    }else {
    toggleState = 0;
  }
  if ((millis() - lastDebounceTime) > debounceDelay) { //EXCEEDS NUMBER OF DEBOUNCE: KEEP RECORD
    current_state = reading;
  	current_fromVal = fromVal;
    digitalWrite(toggle, current_state);
    toggleState = toggleState;
  } 
  current_state = reading;
  current_fromVal = fromVal;

  
  if (toggleState == 1){ // CHANGE IN STATE
    if (digitalRead(toggle) == 1){ //count up
      i = upCounter(current_fromVal);
    }else if (digitalRead(toggle) == 0){ //count down
      i = downCounter(current_fromVal);
  	}
    cycleCounter++;
    if (cycleCounter == 9){
      tone(13, 1000, 1000);
      cycleCounter = 0;
    }
  }else if (toggleState == 0){ //NO CHANGE IN STATE
    if (digitalRead(toggle) == 1){ //count up
      i = upCounter(i);
    }else if (digitalRead(toggle) == 0){ //count down
      i = downCounter(i);
  	}
  }
}






void sevenSegDisplay(byte digit) {
  byte pin = 2;
  for (byte segCount = 0; segCount < 7; ++segCount) {
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    ++pin;
  }
  delay(750);
}


int upCounter(int i) { //UP COUNTER WHEN ON
  if ((i >= 0 )&& (i <= 9)){
    sevenSegDisplay(array[i]);
    i++;
  }
  else if (i > 9){ //repeat array from the start 
    i = 0;
    sevenSegDisplay(array[i]);
    i++;
  }
  return i;
}


int downCounter(int i) {//DOWN COUNTER WHEN OFF 
  if ((i >= 0) && (i <= 9)){ 
    sevenSegDisplay(array[i]);
    i--;
  }
  else if (i < 0){ //repeat array from the start 
    i = 9;
    sevenSegDisplay(array[i]);
    i--;
  }
  return i;
}

int binToDec(int pin1, int pin2, int pin3) {
  int decVal = 0;
  if (pin1 == 1){
    decVal = decVal + 4;
  }
  if (pin2 == 1){
    decVal = decVal + 2;
  }
  if (pin3 == 1){
    decVal = decVal + 1;
  }
  return decVal;
}





void setup() {  
  Serial.begin(9600);


  // FOR SEVEN SEGMENT PINMODE              
  for (int j = 2; j < 9; j++){
    pinMode(j, OUTPUT);
  }
  // FOR INPUT SWITCHES
  // for (int j = 9; j < 14; j++){
  //   digitalWrite(j, INPUT); 
  // }

  for (int j = 2; j < 9; j++){
    digitalWrite(j, current_state);
  } 
}




void loop() { 

  lcd.init();
  lcd.backlight();
  lcd.clear();

  lcd.print("STARTING COUNT");
  lcd.home();

  int fromVal;

  char key = keypad.getKey();
  if (key){
    Serial.println(key);

    lcd.setCursor(0, 1);
    lcd.print(key);
    fromVal = lcd.write(key);
  }





  reading = digitalRead(toggle); 
  
  if ((reading != current_state) || (fromVal != current_fromVal)){ //ANY CHANGE IN STATE
    lastDebounceTime = millis();
    toggleState = 1;
    }else {
    toggleState = 0;
  }
  if ((millis() - lastDebounceTime) > debounceDelay) { //EXCEEDS NUMBER OF DEBOUNCE: KEEP RECORD
    current_state = reading;
  	current_fromVal = fromVal;
    digitalWrite(toggle, current_state);
    toggleState = toggleState;
  } 
  current_state = reading;
  current_fromVal = fromVal;

  
  if (toggleState == 1){ // CHANGE IN STATE
    if (digitalRead(toggle) == 1){ //count up
      i = upCounter(current_fromVal);
    }else if (digitalRead(toggle) == 0){ //count down
      i = downCounter(current_fromVal);
  	}

    // cycleCounter++;
    // if (cycleCounter == 9){
    //   tone(13, 1000, 1000);
    //   cycleCounter = 0;
    // }

  }else if (toggleState == 0){ //NO CHANGE IN STATE
    if (digitalRead(toggle) == 1){ //count up
      i = upCounter(i);
    }else if (digitalRead(toggle) == 0){ //count down
      i = downCounter(i);
  	}
  }
}






void sevenSegDisplay(byte digit) {
  byte pin = 2;
  for (byte segCount = 0; segCount < 7; ++segCount) {
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    ++pin;
  }
  delay(750);
}


int upCounter(int i) { //UP COUNTER WHEN ON
  if ((i >= 0 )&& (i <= 9)){
    sevenSegDisplay(arrayName[i]);
    i++;
  }
  else if (i > 9){ //repeat arrayName from the start 
    i = 0;
    sevenSegDisplay(arrayName[i]);
    i++;
  }
  return i;
}


int downCounter(int i) {//DOWN COUNTER WHEN OFF 
  if ((i >= 0) && (i <= 9)){ 
    sevenSegDisplay(arrayName[i]);
    i--;
  }
  else if (i < 0){ //repeat arrayName from the start 
    i = 9;
    sevenSegDisplay(arrayName[i]);
    i--;
  }
  return i;
}

int binToDec(int pin1, int pin2, int pin3) {
  int decVal = 0;
  if (pin1 == 1){
    decVal = decVal + 4;
  }
  if (pin2 == 1){
    decVal = decVal + 2;
  }
  if (pin3 == 1){
    decVal = decVal + 1;
  }
  return decVal;
}


