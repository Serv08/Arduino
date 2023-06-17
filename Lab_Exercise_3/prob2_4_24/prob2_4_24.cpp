void setup() {
  Serial.begin(9600); // initialize serial communication at 9600 baud
  Serial.println("Color Mix");
}

void loop() {
  String color1, color2;
  
  // asks the user to enter the names of two primary colors
  Serial.println("Enter first primary color (red, blue, or yellow): ");
  while (!Serial.available()); // wait for user input
  color1 = Serial.readStringUntil('\n'); // read user input
  Serial.print("First color: ");
  Serial.println(color1);
  
  Serial.println("Enter second primary color (red, blue, or yellow):");
  while (!Serial.available()); // wait for user input
  color2 = Serial.readStringUntil('\n'); // read user input
  Serial.print("First color: ");
  Serial.println(color2);
  
  // check if the entered colors are valid primary colors
  if ((color1 == "red" || color1 == "blue" || color1 == "yellow") &&
      (color2 == "red" || color2 == "blue" || color2 == "yellow")) {
      
    // mix the colors and print the result
    if ((color1 == "red" && color2 == "blue") || (color1 == "blue" && color2 == "red")) {
      Serial.print("mixed color: ");
      Serial.println("Purple"); 
    } else if ((color1 == "red" && color2 == "yellow") || (color1 == "yellow" && color2 == "red")) {
      Serial.print("mixed color: ");
      Serial.println("Orange");
    } else if ((color1 == "blue" && color2 == "yellow") || (color1 == "yellow" && color2 == "blue")) {
      Serial.print("mixed color: ");
      Serial.println("Green");
    }
    
  } else {
    // display an error message if the entered colors are not valid
    Serial.println("Error. Only enter red, blue, or yellow.");
  }
  
  delay(2000); // wait for 2 second before prompting the user again
}