// output
int HEAD_light = 2;
int SIGNAL_LEFT = 3;
int SIGNAL_RIGHT = 4;
int HAZARD_light = 5;

// input
int BTN_HEAD = 6;
int BTN_SIGNAL_L = 7;
int BTN_SIGNAL_R = 8;
int BTN_HAZARD = 9;


void setup() {
  Serial.begin(9600);
  for (int i=2; i<=5; i++){
    pinMode(i, OUTPUT);
  }

  for (int i=6; i<=9; i++){
    pinMode(i, INPUT);
  }
}

void loop() {
  int btn_head = digitalRead(BTN_HEAD);
  int btn_signal_l = digitalRead(BTN_SIGNAL_L);
  int btn_signal_r = digitalRead(BTN_SIGNAL_R);
  int btn_hazard = digitalRead(BTN_HAZARD);

  Serial.print(btn_head);
  Serial.print(btn_signal_l);
  Serial.print(btn_signal_r);
  Serial.println(btn_hazard);

  if ((btn_head == 0) && (btn_signal_l == 0) && (btn_signal_r == 0) && (btn_hazard == 1)){// option 1: hazard is on only 0001
    OFF();
    BLINK(HAZARD_light);
  }

  else if ((btn_head == 0) && ((btn_signal_l == 0) || (btn_signal_l == 1)) && ((btn_signal_r == 0) || (btn_signal_r == 1)) && (btn_hazard == 0)){ // option 2: signal is on only 0xx0
    OFF();
    if (btn_signal_l == 1){
      digitalWrite(SIGNAL_LEFT, HIGH);
      delay(1000);
      digitalWrite(SIGNAL_LEFT, LOW);
      delay(1000);
    } else if (btn_signal_r == 1){
      digitalWrite(SIGNAL_RIGHT, HIGH);
      delay(1000);
      digitalWrite(SIGNAL_RIGHT, LOW);
      delay(1000);
    }
    else {
      digitalWrite(BTN_SIGNAL_L, LOW);
      digitalWrite(BTN_SIGNAL_R, LOW);
    }
  }

  else if ((btn_head == 1) && (btn_signal_l == 0) && (btn_signal_r == 0) && (btn_hazard == 0)){// option 3: headlight is on only 1000
    OFF();
    digitalWrite(HEAD_light, HIGH);
  }

  else if ((btn_head == 0) && ((btn_signal_l == 0) || (btn_signal_l == 1)) && ((btn_signal_r == 0) || (btn_signal_r == 1)) && (btn_hazard == 1)){ // option 4: hazard and signal 0xx1
    OFF();
    if (btn_signal_l == 1){
      digitalWrite(SIGNAL_RIGHT, LOW);
      digitalWrite(SIGNAL_LEFT, HIGH);
      digitalWrite(HAZARD_light, HIGH);
      delay(1000);
      digitalWrite(SIGNAL_LEFT, LOW);
      digitalWrite(HAZARD_light, LOW);
      delay(1000);
    } else if (btn_signal_r == 1){
      digitalWrite(SIGNAL_LEFT, LOW);
      digitalWrite(SIGNAL_RIGHT, HIGH);
      digitalWrite(HAZARD_light, HIGH);
      delay(1000);
      digitalWrite(SIGNAL_RIGHT, LOW);
      digitalWrite(HAZARD_light, LOW);
      delay(1000);
    }
  }

  else if ((btn_head == 1) && ((btn_signal_l == 0) || (btn_signal_l == 1)) && ((btn_signal_r == 0) || (btn_signal_r == 1)) && (btn_hazard == 0)){ // option 5: signal and headlight 1xx0
    OFF();
    digitalWrite(HEAD_light, HIGH);
    if (btn_signal_l == 1){
      digitalWrite(SIGNAL_RIGHT, LOW);
      digitalWrite(SIGNAL_LEFT, HIGH);
      delay(1000);
      digitalWrite(SIGNAL_LEFT, LOW);
      delay(1000);
    } else if (btn_signal_r == 1){
      digitalWrite(SIGNAL_LEFT, LOW);
      digitalWrite(SIGNAL_RIGHT, HIGH);
      delay(1000);
      digitalWrite(SIGNAL_RIGHT, LOW);
      delay(1000);
    }
  }

  else if ((btn_head == 1) && (btn_signal_l == 0) && (btn_signal_r == 0) && (btn_hazard == 1)){ // option 6: hazard and headlight 1001
    OFF();
    digitalWrite(HEAD_light, HIGH);
    digitalWrite(HAZARD_light, HIGH);
    delay(1000);
    digitalWrite(HAZARD_light, LOW);
    delay(1000);
  }

  else if ((btn_head == 1) && ((btn_signal_l == 0) || (btn_signal_l == 1)) && ((btn_signal_r == 0) || (btn_signal_r == 1)) && (btn_hazard == 1)){ // option 7: all are on 1xx1
    OFF();
    digitalWrite(HEAD_light, HIGH);
    if (btn_signal_l == 1){
      digitalWrite(SIGNAL_RIGHT, LOW);
      digitalWrite(SIGNAL_LEFT, HIGH);
      digitalWrite(HAZARD_light, HIGH);
      delay(1000);
      digitalWrite(SIGNAL_LEFT, LOW);
      digitalWrite(HAZARD_light, LOW);
      delay(1000);
    } else if (btn_signal_r == 1){
      digitalWrite(SIGNAL_LEFT, LOW);
      digitalWrite(SIGNAL_RIGHT, HIGH);
      digitalWrite(HAZARD_light, HIGH);
      delay(1000);
      digitalWrite(SIGNAL_RIGHT, LOW);
      digitalWrite(HAZARD_light, LOW);
      delay(1000);
    }
  }

  else {
    OFF();
  }
}

void BLINK(int LIGHT){
  digitalWrite(LIGHT, HIGH);
  delay(1000);
  digitalWrite(LIGHT, LOW);
  delay(1000);
}

void OFF(){
  digitalWrite(HEAD_light, LOW);
  digitalWrite(SIGNAL_LEFT, LOW);
  digitalWrite(SIGNAL_RIGHT, LOW);
  digitalWrite(HAZARD_light, LOW);
}
