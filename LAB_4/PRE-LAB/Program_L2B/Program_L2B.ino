//Program L2B
int array[3] = {2, 3, 4}; //Student Number is 10860. Use N = 0 + 2

void setup() {
  pinMode(2, OUTPUT); // RED
  pinMode(3, OUTPUT); // BLUE
  pinMode(4, OUTPUT); // GREEN

  while (millis()<30000){ // 
    counter();
  }
}
void loop(){
    // DO NOTHING
}

void counter(){
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++){
      int pin = array[j];
      digitalWrite(pin, HIGH);
      delay(1000);
      digitalWrite(pin, LOW);
    }
  }
}