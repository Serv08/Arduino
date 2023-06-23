#include "SevSegShift.h"

#define SHIFT_PIN_SHCP 6
#define SHIFT_PIN_STCP 7
#define SHIFT_PIN_DS   8

// Global variables

int helloIndexer = 11;
uint8_t helloBinary[12] {
  0b00000000, // = blank
  0b00000000, // = blank
  0b00000000, // = blank
  0b01110110, // = H
  0b01111001, // = E
  0b00111000, // = L
  0b00111000, // = L
  0b00111111, // = O
  0b00000000, // = blank
  0b00000000, // = blank
  0b00000000, // = blank
  0b00000000  // = blank
};

int byeIndexer = 0;
uint8_t byeBinary[10] = {
  0b00000000, // = blank
  0b00000000, // = blank
  0b00000000, // = blank
  0b00000000, // = blank
  0b01111100, // = b
  0b01101110, // = y
  0b01111001, // = E
  0b00000000, // = blank
  0b00000000, // = blank
  0b00000000  // = blank
};

// int counter = 0;
// uint8_t[2] = {
//   0b00000000
// }

// setup for LDR
int ldr1Pin = A0; 
int ldr2Pin = A1;


/* Instantiate a seven segment controller object with:
  - segment pins controlled via 1 shift register and 
  - digit pins connected to the Arduino directly
  */
SevSegShift sevsegshift(
                  SHIFT_PIN_DS, 
                  SHIFT_PIN_SHCP, 
                  SHIFT_PIN_STCP, 
                  1, /* number of shift registers there is only 1 Shiftregister 
                        used for all Segments (digits are on Controller)
                        default value = 2 (see SevSegShift example)
                        */
                  true /* Digits are connected to Arduino directly 
                          default value = false (see SevSegShift example)
                        */
                );

void setup() {
  Serial.begin(9600);
  byte numDigits = 4;
  byte digitPins[] = {5, 4, 3, 2}; // These are the PINS of the ** Arduino **
  byte segmentPins[] = {0, 2, 4, 6, 7, 1, 3, 5}; // these are the PINs of the ** Shift register **
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_ANODE; // See README.md for options
  bool updateWithDelays = true; // Default 'false' is Recommended
  bool leadingZeros = true; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = true; // Use 'true' if your decimal point doesn't exist or isn't connected
  
  sevsegshift.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
  sevsegshift.setBrightness(100);
}

void loop() {

  if (isLDREnabled(ldr1Pin) == 1) {
    displayHello();
  } else { // if (isLDREnabled(ldr2Pin) == 1)
    displayBye();
  }   
  sevsegshift.refreshDisplay(); // Must run repeatedly
}

void displayHello() {
  Serial.println(helloIndexer);
  uint8_t segs[4] = {
    helloBinary[helloIndexer-3], 
    helloBinary[helloIndexer-2], 
    helloBinary[helloIndexer-1], 
    helloBinary[helloIndexer]
  };
  sevsegshift.setSegments(segs);
  
  if (helloIndexer == 3) {
    helloIndexer = 11;
  }
  helloIndexer -= 1;
  delay(75);
}

void displayBye() {
  Serial.println(helloIndexer);
  uint8_t segs[4] = {
    byeBinary[byeIndexer], 
    byeBinary[byeIndexer+1], 
    byeBinary[byeIndexer+2], 
    byeBinary[byeIndexer+3]
  };
  sevsegshift.setSegments(segs);
  
  if (byeIndexer == 6) {
    byeIndexer = 0;
  }
  byeIndexer += 1;
  delay(75);
}

bool isLDREnabled(int analogPin) {
  if (checkPWMValue(analogPin) > 1000) {
  	return 1;
  } else {
  	return 0;
  }
}

int checkPWMValue(int analogPin) {
  int ldrValue = analogRead(analogPin);
  int pwmValue = map(ldrValue, 0, 1023, 0, 255);
  Serial.print("LDR connected to ");
  Serial.print(analogPin);
  Serial.print("'s PWM value: ");
  Serial.println(pwmValue);

  return pwmValue;
}
