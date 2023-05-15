//PROGRAM 5
 //Student Number is 10860. Use N = 0 + 2
void setup() {
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    
}
void loop(){
    Blink(3, 10000);  // GREEN
    Blink(4, 1000); // YELLOW
    Blink(5, 8000);  // RED
}

void Blink(int pin, int dly){ //function to call
    digitalWrite(pin, HIGH);
    delay(dly);
    digitalWrite(pin, LOW);
}