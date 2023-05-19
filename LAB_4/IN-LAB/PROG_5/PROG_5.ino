//PROGRAM 5
 //Student Number is 10860. Use N = 0 + 2

int GREEN1 = 2;
int YELLOW1 = 3;
int RED1 = 4;

int GREEN2 = 5;
int YELLOW2 = 6;
int RED2 = 7;

void setup() {
    for (int i=2; i<=7; i++){
      pinMode(i, OUTPUT);
    }
    
}
void loop(){
  digitalWrite(YELLOW2, LOW);
  digitalWrite(RED1, LOW);
  digitalWrite(GREEN1, HIGH);
  digitalWrite(RED2, HIGH);
  delay(10000);

  digitalWrite(GREEN1, LOW);
  digitalWrite(YELLOW1, HIGH);
  delay(1000);

  digitalWrite(RED1, HIGH);
  digitalWrite(RED2, LOW);
  digitalWrite(YELLOW1, LOW);
  digitalWrite(GREEN2, HIGH);
  delay(8000);

  digitalWrite(YELLOW2, HIGH);
  digitalWrite(GREEN2, LOW);
  delay(1000);
}