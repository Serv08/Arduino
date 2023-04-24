int x;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Using else_if");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Enter a number between 1-9: ");

  while (!Serial.available()); // wait for user input
  String x_string = Serial.readStringUntil('\n');
  int x = x_string.toInt();
  Serial.println(x);

  // if digit 1-3, multiply by 10
  if(x >=1 && x<=3){
    x = x*10;
    Serial.println(x);
  }
  // if 4-6, multiply by 100
  else if(x >=4 && x<=6){
    x = x*100;
    Serial.println(x);
  }
  // if 7-9, multiply by 1000
  else if(x >=7 && x<=9){
    x = x*1000;
    Serial.println(x);
  }
  // if 0 or not a digit, print error statement
  else{
    Serial.println("ERROR!");
  }


  
}