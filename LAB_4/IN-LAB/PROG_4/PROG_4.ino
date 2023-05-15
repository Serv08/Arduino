//PROGRAM 4
 //Student Number is 10860. Use N = 0 + 2
void setup() {
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    
}
void loop(){
    Blink(3);
    Blink(4);    
}

void Blink(int pin){ //function to call
    digitalWrite(pin, HIGH);
    delay(750);
    digitalWrite(pin, LOW);
    delay(750);
}