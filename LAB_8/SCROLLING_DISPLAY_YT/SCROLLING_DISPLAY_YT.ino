#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

char * greetings = "WELCOME TO THE PUP-CPE DEPARTMENT";
char * goodbye = "GOODBYE, SEE YOU AGAIN NEXT TIME!!!!";

int linenumber = 1;
int cursor = 0;

void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  Serial.begin(9600);
}


void loop() {
  updateLCD(greetings);
  delay(500);
}


void updateLCD(){
  int lenOfGreetings = strlen(greetings);

  if (cursor == (lenOfGreetings - 1){
    cursor = 0;
  }
  lcd.setCursor(0, lineNumber);
  if (cursor < lenOfGreetings - 16){
    for ( int iChar = cursor; iChar < cursor + 16, iChar++){
      lcd.print(greetings[iChar]);
    }
  }
  else {
    for (int iChar = cursor; iChar <(lenOfGreetings - 1); iChar++){
      lcd.print(greetings[iChar]);
    }
    for (int iChar = 0; iChar <= 16 - (lenOfGreetings - cursor); iChar++){
      lcd.print(greetings[iChar]);
    }
  }

  cursor++;
}
