
// PROGRAM L2A
int LED = 2; //Student Number is 10860. Use N = 0 + 2

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for half a second
  digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
  delay(500);                       // wait for half a second
}