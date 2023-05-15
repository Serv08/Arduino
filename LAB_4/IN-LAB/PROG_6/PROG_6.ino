int LEDS[8] = {2,3,4,5,6,7,8,9}; // pins for all 
int i; // used for loops

int button1;
int button2;
int button3;

int button1_SWITCH = 10;
int button2_SWITCH = 11;
int button3_SWITCH = 12;


void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);     // pins for OUTPUT
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  pinMode(10, INPUT);     // pins for SWITCH inputs
  pinMode(11, INPUT);
  pinMode(12, INPUT);
}


void loop() {

  button1 = digitalRead(button1_SWITCH);
  button2 = digitalRead(button2_SWITCH);
  button3 = digitalRead(button3_SWITCH);


  int inputs = binaryToDecimal(button1, button2, button3);

  delay(1000);

  // MAIN SWITCH CASES
  switch (inputs){
    case 0:
      off();
      break;
    case 1:
      serialOutput(inputs);
      case_1();
      break;

    case 2:
      serialOutput(inputs);
      case_2();
      break;

    case 3:
      serialOutput(inputs);
      case_3();
      break;

    case 4:
      serialOutput(inputs);
      case_4();
      break;


    default:
      Serial.print("INPUT OUT OF RANGE: ");
      Serial.println(inputs);
      Serial.println("RESET");
      case_5();
      delay(1000);
      break;
  }
}


// FUNCTIONS
void case_1(){
  for (i = 0; i<4; i++){
        doubleBlink(LEDS[3-i], LEDS[4+i]);
      }
}

void case_2(){
  for (i = 0; i<4; i++){
          doubleBlink(LEDS[i], LEDS[7-i]);
        }
}

void case_3(){
  for (i = 0; i<8; i = i+2){
    Blink(LEDS[i]);
  }
  for (i = 7; i>0; i = i-2){
    Blink(LEDS[i]);
  }
  // off();
}

void case_4(){
  for (i=0; i<4; i++){
    Blink(LEDS[i]);
    Blink(LEDS[7-i]);
  }
  // off();
}

void case_5(){
  for (i = 8; i>0; i--){
    for (int j = 0; j < i; j++){
      digitalWrite(LEDS[j], HIGH);
      delay(100);
    }
    off();
  }
}

// Binary to decimal converter
int binaryToDecimal(int SW1, int SW2, int SW3){
	int dec = 0;
	if (SW1 == 1)
		dec = dec + 1;
	if (SW2 == 1)
		dec = dec + 2;
	if (SW3 == 1)
		dec = dec + 4;
	return dec;
}

void Blink(int pin){ 
  digitalWrite(pin, HIGH);
  delay(500);
  digitalWrite(pin, LOW);
  delay(500);
}

void quickBlink(int pin){ 
  digitalWrite(pin, HIGH);
  delayMicroseconds(100);
  digitalWrite(pin, LOW);
  delayMicroseconds(100);
}

void doubleBlink(int forward_pin, int backward_pin){
  digitalWrite(forward_pin, HIGH);
  digitalWrite(backward_pin, HIGH);
  delay(500);
  digitalWrite(forward_pin, LOW);
  digitalWrite(backward_pin, LOW);
  delay(500);
}

void off(){
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
}

void on(){
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
}

void serialOutput(int input){
  Serial.print("SWITCH CASE INPUT: ");
  Serial.println(input);
}