int toggle = 9, i = 0; 
int counter = 0, reading; 
int current_state = LOW;
long time = 0;
int debounce_count = 10;
int array[10] = {0,1,2,3,4,5,6,7,8,9};
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
void setup() {                
  pinMode(2, OUTPUT);   
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(toggle, INPUT); 
  for (int j = 2; j < 9; j++){
    digitalWrite(j, current_state);
  } 
  //writeDot(0);  // start with the "dot" off
}
void sevenSegDisplay(byte digit) {
  byte pin = 2;
  for (byte segCount = 0; segCount < 7; ++segCount) {
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    ++pin;
  }
  delay(750);
}
void upCounter() { //UP COUNTER WHEN ON
  if ((i >= 0 )&& (i <= 9)){
    sevenSegDisplay(array[i]);
    i++;
  }
  else if (i > 9){ //repeat array from the start 
    i = 0;
    sevenSegDisplay(array[i]);
    i++;
  }
}
void downCounter() {//DOWN COUNTER WHEN OFF 
  if ((i >= 0) && (i <= 9)){ 
    sevenSegDisplay(array[i]);
    i--;
  }
  else if (i < 0){ //repeat array from the start 
    i = 9;
    sevenSegDisplay(array[i]);
    i--;
  }
}
void loop() {
  if (millis() != time) {
    reading = digitalRead(toggle);
    if (reading == current_state && counter > 0){ // NO CHANGES
      counter--;
    }
    if (reading != current_state){ //CHANGE STATE
      counter++;
    }
    if (counter >= debounce_count){ //EXCEEDS NUMBER OF DEBOUNCE: KEEP RECORD
      counter = 0;
      current_state = reading; 
      digitalWrite(toggle, current_state); 
    }
    time = millis();
  }
  if (digitalRead(toggle) == HIGH){ // SWITCH IS ON
    upCounter();
	} else if (digitalRead(toggle) == LOW){ // SWITCH IS OFF
    downCounter();
  }
}