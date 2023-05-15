// PROGRAM 3
int LED = 3; //Group number 1. Use N = 1 + 2

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(750);                       // wait for 0.75 second
  digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
  delay(750);                       // wait for 0.75 second
}