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
int green = 9, yellow = 10, red = 11;
void setup() {                
  pinMode(2, OUTPUT);   
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  writeDot(0);  // start with the "dot" off
}
void writeDot(byte dot) {
  digitalWrite(9, dot);
}
void sevenSegWrite(byte digit) {
  byte pin = 2;
  for (byte segCount = 0; segCount < 7; ++segCount) {
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    ++pin;
  }
}
void downCounter(byte digit) {
  for (byte count = digit; count > 0; count--) {
    byte pin = 2;
    sevenSegWrite(count);
    delay(1000);
  }
}
void trafficLight(int ledColor, int time){
  int times = 1000 * time;
  analogWrite(ledColor, 255);
  downCounter(time);
  analogWrite(ledColor, 0);
  //Serial.println("DONE");
}
void loop() {
  //Serial.println("GREEN!");
  trafficLight(green, 9);
  //Serial.println("YELLOW!");
  trafficLight(yellow, 1);
  //Serial.println("RED!");
  trafficLight(red, 8);
}