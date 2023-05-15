// reads time in numeric form and prints in english
// input is "hours_space_minutes"

//HOURS
String hrName[12] = {"One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve"};

//MINUTES
String minName[60] = {"o'clock", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", 
  "ten", "eleven", "twelve", "thirteen", "forteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen", 
  "twenty", "thirty", "forty", "fifty"};

void setup() {
  Serial.begin(9600); // baud rate

  char again;
  do{
    Serial.println(""); // new line

    // USER INPUT
    String time = userString();
    Serial.println(time);
    
    // Split the string 
    String hrsStr = time.substring(0,2); // first index of user input is hours
    String minStr = time.substring(2,5); // second index of user input is minutes
    // Serial.println(hrsStr);
    // Serial.println(minStr);
    // Serial.println("Hello world");

    // CONVERTS NUM TIME TO WORDED TIME
    int hrs = hrsStr.toInt();
    int min = minStr.toInt();
    // Serial.println(hrs);
    // Serial.println(min);

    // SPECIAL CASES
    // condition for Midnight
    if ((hrs == 0) && (min == 0)){
      Serial.println("Midnight");
    }
    // condition for Noon
    else if ((hrs == 12) && (min == 0)){
      Serial.println("Noon");
    }
    else {

      // PRINTING TIME
      if (hrs==12){
        // NOON 
        Serial.print(hrName[hrs-1]);
        Serial.print(" ");
        Serial.print(minuteINDEX(min));
        Serial.println(" NN");
      } else if (hrs/12 > 0){
        // NIGHT
        Serial.print(hrName[(hrs-12)-1]);
        Serial.print(" ");
        Serial.print(minuteINDEX(min));
        Serial.println(" PM");
      } else {
        // MORNING
        Serial.print(hrName[hrs-1]);
        Serial.print(" ");
        Serial.print(minuteINDEX(min));
        Serial.println(" AM");
      }
    }

      // STOPS LOOP
      Serial.print("Do you want to try again (Y/N): "); // asks user
      while(!Serial.available()); // waits for user input
      again = Serial.read();
      Serial.println(again);
      if (again == 'N'){
        Serial.println("---------------------DONE---------------------");
        //while(!Serial.available()); // waits for user input indefinitely
      }
  }while(again == 'Y');
}

void loop() {
}

int minuteINDEX(int min){
  int tens = (min/10)*10;
  int ones = min-tens;
  if (min<20)
    Serial.print(minName[min]);
  else{
    Serial.print(minName[tens]);
    Serial.print("-");
    Serial.print(minName[ones]);
  }
}

String userString(){
  Serial.print("Enter time: ");
  while(!Serial.available()); // waits for the user input
  String input = Serial.readString();
  
  return input;
}