
int toggle = 9, i = 0; 

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
void setup() {                
  for (int j = 2; j < 9; j++){
    pinMode(j, OUTPUT);
  }
  for (int j = 9; j < 14; j++){
    digitalWrite(j, INPUT); 
  }
  for (int j = 2; j < 9; j++){
    digitalWrite(j, current_state);
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

void loop() { 
  //READ ALL SWITCH AND PINS
  pin1 = digitalRead(10); //most significant bit
  pin2 = digitalRead(11);
  pin3 = digitalRead(12); //least significant bit
  reading = digitalRead(toggle);
  //CONVERT DPST READING TO DECIMAL VALUE
  int fromVal = binToDec(pin1, pin2, pin3); 
  
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
  }else if (toggleState == 0){ //NO CHANGE IN STATE
    if (digitalRead(toggle) == 1){ //count up
      i = upCounter(i);
    }else if (digitalRead(toggle) == 0){ //count down
      i = downCounter(i);
  	}
  }
  
}