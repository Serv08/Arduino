#include <Wire.h>

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display
int r1 = A2;
int r2 = A3;
int cnt1 = 1, cnt2 = 1;

String byeMessage = "GOODBYE AND SEE YOU AGAIN!!";
String helloMessage = "WELCOME TO CPE DEPARTMENT!!";

void setup() {
  Serial.begin(9600);
  pinMode(r1, INPUT);
  pinMode(r2, INPUT);
  lcd.init();         // set up the LCD 16x2
  lcd.backlight();
}
void loop() {
  int value1 = analogRead(r1); // left LDR
  int value2 = analogRead(r2); // right LDR
  Serial.print("value1:"); Serial.println(value1);
  Serial.print("value2:"); Serial.println(value2);
  if (value1 > 150){
    scrollMessage(0, helloMessage, 250, 16);
  } else if (value1 < 150){
    clearLine(1);
    cnt1 = 1;
  }
  
  if (value2 > 150){
    scrollMessage(1, byeMessage, 250, 16);
  } else if (value2 < 150){
    clearLine(0);
    cnt2 = 1;
  }
}

void scrollMessage(int row, String message, int delayTime, int totalColumns) {
  // exchange totalColumns and zero and increment 1 to i to change the direction to right to left
  for (int i=totalColumns; i > 0; i--) { 
    message = " " + message; // to display spaces at the front of the message
  } 
  message = message + " "; // to display spaces before the message was displayed in lcd
  // exchange message.length and zero and increment 1 to position to change the direction to right to left
  for (int position = message.length(); position > 0; position--) { 
    lcd.setCursor(0, row);
    /* 
    look for index 'position' until 'position + totalColumns'
    to print each character in message in their right position 
    while the message is moving 1 block at a time in lcd display
    */
    lcd.print(message.substring(position, position + totalColumns)); 
    delay(delayTime);
  }
}

void clearLine(int line){
  lcd.setCursor(0,line);
  for(int n = 0; n < 16; n++){
    lcd.print(" ");
  }
}