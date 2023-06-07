int LEDS [9] = {13,12,11,10, 9 ,8,7,6,5};

int BUTTON1 = 2;
int BUTTON2 = 3;
int BUTTON3 = 4;


void setup() {
  Serial.begin(9600);
  for (int i = 5; i <= 13; i++){
    pinMode(i, OUTPUT);
  }
  for (int i = 2; i <= 4; i++){
    pinMode(i, INPUT);
  }
}

void loop() {
  int btn1 = digitalRead(BUTTON1);
  int btn2 = digitalRead(BUTTON2);
  int btn3 = digitalRead(BUTTON3);

  int choice = BINARY(btn1, btn2, btn3);
  Serial.println(choice);

  if (choice == 1){
    OFF();
    SIREN1();
  }
  else if (choice == 2){
    OFF();
    SIREN2();
  }
  else if (choice == 3){
    OFF();
    SIREN3();
  }
  else if (choice == 4){
    SIREN4();
  }
  else if (choice == 5){
    SIREN5();
  }
  else{
    OFF();
  }
}

int BINARY(int FIRST, int SECOND, int THIRD){
  int decimal = 0;
  if (FIRST == 1)
    decimal = decimal + 4;
  if (SECOND == 1)
    decimal = decimal + 2;
  if (THIRD == 1)
    decimal = decimal + 1;
  return decimal;
}

void SIREN1(){
  // INCREASING FREQUENCY

  // LED PATTERN - normal running light pattern
  for (int i = 0; i <9; i++){
    digitalWrite(LEDS[i], HIGH);
    delay(100);
    digitalWrite(LEDS[i], LOW);
  }

}

void SIREN2(){
  // elephant/battle trumpet SOUND

  // LED PATTERN - from middle outwards
  digitalWrite(LEDS[4], HIGH);
  
  for (int i = 0; i<4; i++){
    digitalWrite(LEDS[3-i], HIGH);
    digitalWrite(LEDS[5+i], HIGH);
    delay(100);
  }

  for (int i = 0; i<4; i++){
    digitalWrite(LEDS[i], LOW);
    digitalWrite(LEDS[8-i], LOW);
    delay(100);
  }
  delay(100);
}

void SIREN3(){
  // AMBULANCE (woooooweeeeeeewooooooweeeeee)

  // LED PATTERN - alternatating pattern na sabay sa tunog
  digitalWrite(LEDS[6], LOW);
  digitalWrite(LEDS[7], LOW);
  digitalWrite(LEDS[8], LOW);
  digitalWrite(LEDS[0], HIGH);
  digitalWrite(LEDS[1], HIGH);
  digitalWrite(LEDS[2], HIGH);
  delay(500);
  digitalWrite(LEDS[0], LOW);
  digitalWrite(LEDS[1], LOW);
  digitalWrite(LEDS[2], LOW);
  digitalWrite(LEDS[6], HIGH);
  digitalWrite(LEDS[7], HIGH);
  digitalWrite(LEDS[8], HIGH);
  delay(500);
}

void SIREN4(){
  // WEWEWEWEW

  // LED PATTERN - to and fro running light
  for (int i=0; i<9; i++){
    digitalWrite(LEDS[i], HIGH);
    delay(100);
    digitalWrite(LEDS[i], LOW);
  }
  for (int i=9; i>0; i--){
    digitalWrite(LEDS[i], HIGH);
    delay(100);
    digitalWrite(LEDS[i], LOW);
  }
}

void SIREN5(){
  // quick laser sounds or/then slow laser lower sounds

  // LED PATTERN
  for (int i=0; i<3; i++){
    digitalWrite(LEDS[3+i], HIGH);
  }
  load();  
  for (int i=0; i<3; i++){
    digitalWrite(LEDS[3+i], LOW);
  }
  load();
}

void load(){
  for (int i=0; i<3; i++){
    digitalWrite(LEDS[2-i], HIGH);
    digitalWrite(LEDS[6+i], HIGH);
    delay(100);
    digitalWrite(LEDS[2-i], LOW);
    digitalWrite(LEDS[6+i], LOW);
    delay(100);
  }
  for (int i=0; i<3; i++){
    digitalWrite(LEDS[i], HIGH);
    digitalWrite(LEDS[8-i], HIGH);
    delay(100);
    digitalWrite(LEDS[i], LOW);
    digitalWrite(LEDS[8-i], LOW);
    delay(100);
  }
}

void OFF(){
  for (int i=0; i<9; i++){
    digitalWrite(LEDS[i], LOW);
  }
}