//PROGRAM L2C
 //Student Number is 10860. Use N = 0 + 2
void setup() {
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    
    Blink(2, 4);
    Blink(3, 6);
    Blink(4, 3);
}
void loop(){
    
}
void Blink(int pin, int val){ //function to call
    int ctr = 0;
    while (ctr < val){
        digitalWrite(pin, HIGH);
        delay(500);
        digitalWrite(pin, LOW);
        delay(500);
        ctr++;
    }
}