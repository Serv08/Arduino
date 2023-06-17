#include <Arduino.h>

#define TONE_USE_INT
#define TONE_PITCH 440
#include <TonePitch.h>
#include <Keypad.h>

const byte ROWS =4; 
//four rows
const byte COLS =4; 
//four columns
//define the cymbolson the buttons of the keypads
char hexaKeys[ROWS][COLS] ={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

//connect to the row pinouts of the keypad
byte rowPins[ROWS] ={9,8,7,6}; // {row4, row3, row2, row1}

//connect to the column pinouts of the keypad
byte colPins[COLS] ={2,3,4,5}; // {col4, col3, col2, col1}

//initialize an instance of class NewKeypad
Keypad customKeypad =Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

// variables
int pinLED[5] = {10,11,12,13,A1};
int buzzerPin = A0;
int p = buzzerPin;

// notes for easy timing
int quarter = 100 * 4; // quarter note, equivalent to bpm
int eight = quarter/2; // eighth note
int sixteen = eight/2; // sixteenth note
int half = quarter*2; // half note
int whole = half * 2;

int bahayKuboNotes[86][2] = {
  {NOTE_C5, half},
  {NOTE_G4, quarter},
  {NOTE_D5, quarter},
  {NOTE_B4, half},
  {NOTE_G4, quarter},
  {NOTE_A4, half},
  {NOTE_B4, quarter},
  {NOTE_G4, half},
  {NOTE_E4, eight},
  {NOTE_F4, eight},
  {NOTE_G4, quarter},
  {NOTE_A4, quarter},
  {NOTE_G4, quarter},
  {NOTE_F4, half},
  {NOTE_D5, quarter},
  {NOTE_D5, quarter},
  {NOTE_E5, quarter},
  {NOTE_D5, quarter},
  {NOTE_C5, half},
  {NOTE_G4, eight},
  {NOTE_G4, eight},
  {NOTE_C5, half},
  {NOTE_D5, eight},
  {NOTE_C5, eight},
  {NOTE_B4, half},
  {NOTE_G4, eight},
  {NOTE_G4, eight},
  {NOTE_A4, eight},
  {NOTE_A4, eight},
  {NOTE_B4, quarter},
  {NOTE_A4, quarter},
  {NOTE_G4, half},
  {NOTE_G4, quarter},
  {NOTE_A4, half},
  {NOTE_A4, quarter},
  {NOTE_B4, quarter + eight},
  {NOTE_A4, eight},
  {NOTE_G4, quarter},
  {NOTE_C5, half + quarter + half},
  {NOTE_G4, quarter},
  {NOTE_C5, quarter + eight},
  {NOTE_D5, eight},
  {NOTE_C5, quarter},
  {NOTE_B4, half},
  {NOTE_G4, quarter},
  {NOTE_A4, quarter},
  {NOTE_A4, eight},
  {NOTE_B4, eight},
  {NOTE_A4, quarter},
  {NOTE_G4, half}, // changed from g4
  {NOTE_E4, eight}, 
  {NOTE_F4, eight},
  {NOTE_G4, quarter},
  {NOTE_A4, quarter},
  {NOTE_G4, quarter},
  {NOTE_F4, half},
  {NOTE_D5, eight},
  {NOTE_D5, eight},
  {NOTE_D5, quarter},
  {NOTE_E5, quarter},
  {NOTE_D5, quarter},
  {NOTE_C5, quarter + eight},
  {NOTE_G4, eight},
  {NOTE_G4, quarter},
  {NOTE_C5, quarter + eight},
  {NOTE_D5, eight},
  {NOTE_C5, quarter},
  {NOTE_B4, half},
  {NOTE_B4, quarter},
  {NOTE_A4, quarter},
  {NOTE_A4, quarter},
  {NOTE_B4, quarter},
  {NOTE_G4, half},
  {NOTE_G4, eight},
  {NOTE_G4, eight},
  {NOTE_A4, quarter},
  {NOTE_A4, quarter},
  {NOTE_A4, quarter},
  {NOTE_B4, half},
  {NOTE_B4, eight},
  {NOTE_B4, eight},
  {NOTE_B4, quarter},
  {NOTE_A4, quarter},
  {NOTE_B4, quarter},
  {NOTE_C5, half},
  {0, whole},
};

// C D E F G A B
int itsyBitsySpiderNotes[46][2] = {
  {NOTE_G3, eight},
  {NOTE_C4, quarter},
  {NOTE_C4, eight},
  {NOTE_C4, quarter},
  {NOTE_D4, eight},
  //
  {NOTE_E4, quarter + eight},
  {NOTE_E4, quarter},
  {NOTE_E4, eight},
  // bar3
  {NOTE_D4, quarter}, 
  {NOTE_D4, quarter},
  {NOTE_D4, quarter},
  // bar4
  {NOTE_C4, half + quarter},
  // bar5
  {NOTE_E4, quarter + eight},
  {NOTE_E4, quarter}, 
  {NOTE_F4, eight},
  // bar6
  {NOTE_G4, quarter + eight},
  {NOTE_G4, quarter + eight},
  // bar7
  {NOTE_F4, quarter},
  {NOTE_E4, eight},
  {NOTE_F4, quarter},
  {NOTE_G4, eight},
  // bar8
  {NOTE_E4, half + quarter},
  // bar9
  {NOTE_C4, quarter + eight},
  {NOTE_C4, quarter},
  {NOTE_D4, eight},
  // bar10
  {NOTE_E4, quarter + eight},
  {NOTE_E4, quarter + eight},
  // bar 11
  {NOTE_D4, quarter},
  {NOTE_C4, eight},
  {NOTE_D4, quarter},
  {NOTE_E4, eight},
  // bar12
  {NOTE_C4, quarter + eight},
  {NOTE_G3, quarter},
  {NOTE_G3, eight},
  // bar13
  {NOTE_C4, quarter},
  {NOTE_C4, eight},
  {NOTE_C4, quarter},
  {NOTE_D4, eight},
  // bar14
  {NOTE_E4, quarter + eight},
  {NOTE_E4, quarter},
  {NOTE_E4, eight},
  // bar15
  {NOTE_D4, quarter},
  {NOTE_C4, eight},
  {NOTE_D4, quarter},
  {NOTE_E4, eight},
  {NOTE_C4, half + quarter},
};

int twinkleTwinkleNotes[42][2] {
  {NOTE_C4, quarter},
  {NOTE_C4, quarter},
  {NOTE_G4, quarter},
  {NOTE_G4, quarter},
  {NOTE_A4, quarter},
  {NOTE_A4, quarter},
  {NOTE_G4, quarter + eight},
  {NOTE_F4, quarter},
  {NOTE_F4, quarter},
  {NOTE_E4, quarter},
  {NOTE_E4, quarter},
  {NOTE_D4, quarter},
  {NOTE_D4, quarter},
  {NOTE_C4, quarter + eight},
  {NOTE_G4, quarter},
  {NOTE_G4, quarter},
  {NOTE_F4, quarter + eight},
  {NOTE_F4, eight},
  {NOTE_E4, quarter},
  {NOTE_E4, quarter},
  {NOTE_D4, quarter + eight},
  {NOTE_G4, quarter},
  {NOTE_G4, quarter},
  {NOTE_F4, quarter},
  {NOTE_F4, quarter},
  {NOTE_E4, quarter},
  {NOTE_E4, quarter},
  {NOTE_D4, quarter + eight},
  {NOTE_C4, quarter},
  {NOTE_C4, quarter},
  {NOTE_G4, quarter},
  {NOTE_G4, quarter},
  {NOTE_A4, quarter},
  {NOTE_A4, quarter},
  {NOTE_G4, quarter + eight},
  {NOTE_F4, quarter},
  {NOTE_F4, quarter},
  {NOTE_E4, quarter},
  {NOTE_E4, quarter},
  {NOTE_D4, quarter},
  {NOTE_D4, quarter},
  {NOTE_C4, quarter + eight}
};

float mult=2.5;
int sitsiritsitNotes[32][2] = {
  {NOTE_G4, sixteen*mult},
  {NOTE_G4, sixteen*mult},
  {NOTE_G4, eight*mult},
  {NOTE_E4, (eight + sixteen)*mult},
  {NOTE_G4, sixteen*mult},
  {NOTE_F4, eight*mult},
  {NOTE_E4, eight*mult},
  {NOTE_D4, quarter*mult},
  {NOTE_F4, sixteen*mult},
  {NOTE_F4, sixteen*mult},
  {NOTE_F4, eight*mult},
  {NOTE_D4, (eight + sixteen)*mult},
  {NOTE_F4, sixteen*mult},
  {NOTE_E4, eight*mult},
  {NOTE_D4, eight*mult},
  {NOTE_C4, quarter*mult},
  {NOTE_G4, sixteen*mult},
  {NOTE_G4, sixteen*mult},
  {NOTE_G4, eight*mult},
  {NOTE_C4, (eight + sixteen)*mult},
  {NOTE_C4, sixteen*mult},
  {NOTE_D4, eight*mult},
  {NOTE_E4, eight*mult},
  {NOTE_F4, quarter*mult},
  {NOTE_F4, sixteen*mult},
  {NOTE_F4, sixteen*mult},
  {NOTE_F4, eight*mult},
  {NOTE_G4, (eight + sixteen)*mult},
  {NOTE_F4, sixteen*mult},
  {NOTE_E4, eight*mult},
  {NOTE_D4, eight*mult},
  {NOTE_C4, quarter*mult}
};

int REST = 0;
int londonBridgeNotes[25][2] {
  {NOTE_C5, eight + sixteen},
  {NOTE_D5, sixteen},
  {NOTE_C5, eight},
  {NOTE_B4, eight},
  {NOTE_A4, eight},
  {NOTE_B4, eight},
  {NOTE_C5, quarter},
  {NOTE_G4, eight},
  {NOTE_A4, eight},
  {NOTE_B4, quarter},
  {NOTE_A4, eight},
  {NOTE_B4, eight},
  {NOTE_C5, quarter},
  {NOTE_C5, eight + sixteen},
  {NOTE_D5, sixteen},
  {NOTE_C5, eight},
  {NOTE_B4, eight},
  {NOTE_A4, eight},
  {NOTE_B4, eight},
  {NOTE_C5, quarter},
  {NOTE_G4, quarter},
  {NOTE_C5, quarter},
  {NOTE_A4, eight},
  {NOTE_D4, eight},
  {REST, quarter}
};

int leronLeronSintaNotes[56][2] = {
  {REST, eight},
  {NOTE_G4, eight},
  {NOTE_G4, eight + sixteen},
  {NOTE_F4, sixteen},
  {NOTE_E4, eight},
  {NOTE_F4, eight},
  {NOTE_G4, quarter},
  {REST, eight},
  {NOTE_G4, quarter},
  {NOTE_A4, eight},
  {NOTE_G4, eight},
  {NOTE_F4, eight},
  {NOTE_G4, eight},
  {NOTE_F4, quarter},
  {REST, eight},
  {NOTE_F4, eight},
  {NOTE_F4, eight + sixteen},
  {NOTE_E4, sixteen},
  {NOTE_D4, eight},
  {NOTE_E4, eight},
  {NOTE_F4, quarter},
  {REST, eight},
  {NOTE_G4, eight},
  {NOTE_G4, eight},
  {NOTE_A4, eight},
  {NOTE_G4, eight},
  {NOTE_F4, eight},
  {NOTE_E4, quarter},
  {REST, eight},
  {NOTE_G4, eight},
  {NOTE_G4, eight},
  {NOTE_F4, eight},
  {NOTE_E4, eight},
  {NOTE_F4, eight},
  {NOTE_G4, quarter},
  {REST, eight},
  {NOTE_E4, eight},
  {NOTE_E4, eight},
  {NOTE_E4, eight},
  {NOTE_F4, eight + sixteen},
  {NOTE_G4, sixteen},
  {NOTE_A4, quarter},
  {REST, eight},
  {NOTE_A4, eight},
  {NOTE_A4, eight},
  {NOTE_C5, eight},
  {NOTE_B4, eight},
  {NOTE_A4, eight},
  {NOTE_G4, quarter},
  {REST, eight},
  {NOTE_C5, eight},
  {NOTE_B4, eight},
  {NOTE_B4, eight},
  {NOTE_A4, eight},
  {NOTE_B4, eight},
  {NOTE_C5, half},
};

void setup(){
  Serial.begin(9600);
  for (int i=0; i<5; i++) {
    pinMode(pinLED[i], OUTPUT);
  }
}

void loop(){
  char option =customKeypad.getKey();
  // if(customKey){
  //   Serial.println(customKey);
  // }
  
  menu();

  if (option == '1') {    
    bahayKubo();
  } 
  if (option == '2') {
    itsyBitsySpider();
  } 
  if (option == '3') {
    twinkleTwinkle();
  } 
  if (option == '4') {
    sitsiritsit();
  } 
  if (option == '5') {
    londonBridge();
  } 
  if (option == '6') {
    leronLeronSinta();
  } else {
    nothingness();
  }
}

void lightItUp(int noteTone) {
  if (noteTone == 0) { 
    for (int i=0; i<5; i++) {
      digitalWrite(pinLED[i], LOW);
    }
  } else if ((noteTone <= NOTE_D4) || (NOTE_C5 <= noteTone)) {
    digitalWrite(pinLED[0], HIGH);
    digitalWrite(pinLED[1], HIGH);
    digitalWrite(pinLED[2], HIGH);
    digitalWrite(pinLED[3], HIGH);
    digitalWrite(pinLED[4], HIGH);
  } else if ((noteTone == NOTE_F4) || (noteTone == NOTE_A4) || (noteTone == NOTE_E4) || (noteTone == NOTE_B4)) {
    digitalWrite(pinLED[0], LOW);
    digitalWrite(pinLED[1], HIGH);
    digitalWrite(pinLED[2], HIGH);
    digitalWrite(pinLED[3], HIGH);
    digitalWrite(pinLED[4], LOW);
  } else if (noteTone == NOTE_G4) {
    digitalWrite(pinLED[0], LOW);
    digitalWrite(pinLED[1], LOW);
    digitalWrite(pinLED[2], HIGH);
    digitalWrite(pinLED[3], LOW);
    digitalWrite(pinLED[4], LOW);
  } else {
    for (int i=0; i<5; i++) {
      digitalWrite(pinLED[i], LOW);
    }
  } 
}

void leronLeronSinta() {
  for (int i=0; i<56; i++) {
    lightItUp(leronLeronSintaNotes[i][0]);
    tone(p, leronLeronSintaNotes[i][0], leronLeronSintaNotes[i][1]);
    delay(leronLeronSintaNotes[i][1]);
  }
}

void londonBridge() {
  for (int i=0; i<25; i++) {
    lightItUp(londonBridgeNotes[i][0]);
    tone(p, londonBridgeNotes[i][0], londonBridgeNotes[i][1]);
    delay(londonBridgeNotes[i][1]);
  }
}

void sitsiritsit() {
  for (int i=0; i<32; i++) {
    lightItUp(sitsiritsitNotes[i][0]);
    tone(p, sitsiritsitNotes[i][0], sitsiritsitNotes[i][1]);
    delay(sitsiritsitNotes[i][1]);
  }
}

void twinkleTwinkle() {
  for (int i=0; i<42; i++) {
    lightItUp(twinkleTwinkleNotes[i][0]);
    tone(p, twinkleTwinkleNotes[i][0], twinkleTwinkleNotes[i][1]);
    delay(twinkleTwinkleNotes[i][1]);
  }
}

void itsyBitsySpider() {
  for (int i=0; i<46; i++) {
    lightItUp(itsyBitsySpiderNotes[i][0]);
    tone(p, itsyBitsySpiderNotes[i][0], itsyBitsySpiderNotes[i][1]);
    delay(itsyBitsySpiderNotes[i][1]);
  }
}

void bahayKubo() {
  for (int i=0; i<86; i++) {
    lightItUp(bahayKuboNotes[i][0]);
    tone(p, bahayKuboNotes[i][0], bahayKuboNotes[i][1]);
    delay(bahayKuboNotes[i][1]);
  }
}

void nothingness() {
}

int menu() {
  Serial.println("");
  Serial.println("");
  Serial.println("<<<< ARDUINO JUKE BOX >>>>");
  Serial.println("1. Bahay Kubo");
  Serial.println("2. Itsy Bitsy Spider");
  Serial.println("3. Twinkle Twinkle Little Star");
  Serial.println("4. Sitsiritsit");
  Serial.println("5. London Bridge is Falling Down");
  Serial.println("6. Leron Leron Sinta");
  Serial.println("");
  Serial.print("Pick your song: ");
}
