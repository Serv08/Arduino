void setup() {
  Serial.begin(9600);
  Serial.println("Switch case");
}

void loop() {
  Serial.print("Enter a number: ");

  while (!Serial.available()); // wait for user input
  String x_string = Serial.readStringUntil('\n');
  int x = x_string.toInt();
  Serial.println(x);
  
  switch (x) {
    case 1:
      oneToThree(x);
      break;
    
    case 2:
      oneToThree(x);
      break;

    case 3:
      oneToThree(x);
      break;

    case 4:
      fourToSix(x);
      break;
    
    case 5:
      fourToSix(x);
      break;

    case 6:
      fourToSix(x);
      break;

    case 7:
      sevenToNine(x);
      break;

    case 8:x`
      sevenToNine(x);
      break;

    case 9:
      sevenToNine(x);
      break;    

    default:
      Serial.println("ERROR");
  }
}

int oneToThree(int x){
  return Serial.println(x*10);
}

int fourToSix(int x){
  return Serial.println(x*100);
}

int sevenToNine(int x){
  return Serial.println(x*1000);
}