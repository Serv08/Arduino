#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
// LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
LiquidCrystal_I2C lcd(0x27, 16, 2);
long first = 0;
long second = 0;
double total = 0;
char customKey;
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','*'},
  {'C','0','=','/'}
};
byte rowPins[ROWS] = {9,8,7,6}; 
byte colPins[COLS] = {2,3,4,5}; 
Keypad customKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); 

void setup()
{              
lcd.init();
lcd.backlight();
lcd.clear();
lcd.home();
}

void loop()
{
  customKey = customKeypad.getKey();
  switch(customKey) 
  {
  case '0' ... '9': 
    lcd.setCursor(0,0);
    first = first * 10 + (customKey - '0');
    lcd.print(first);
    break;
  case '+':
    first = (total != 0 ? total : first);
    lcd.setCursor(0,1); // setCursor(col, row);
    lcd.print("+");
    second = SecondNumber(); // get the collected the second number
    total = first + second;
    lcd.setCursor(0,1);
    lcd.print(total);
    first = 0, second = 0; // reset values back to zero for next use
    break;
  case '-':
    first = (total != 0 ? total : first);
    lcd.setCursor(0,1);
    lcd.print("-");
    second = SecondNumber();
    total = first - second;
    lcd.setCursor(0,3);
    lcd.print(total);
    first = 0, second = 0;
    break;
  case '*':
    first = (total != 0 ? total : first);
    lcd.setCursor(0,1);
    lcd.print("*");
    second = SecondNumber();
    total = first * second;
    lcd.setCursor(0,3);
    lcd.print(total);
    first = 0, second = 0;
    break;
  case '/':
    first = (total != 0 ? total : first);
    lcd.setCursor(0,1); 
    lcd.print("/");
    second = SecondNumber();
    lcd.setCursor(0,1);
    second == 0 ? lcd.print("Invalid") : total = (float)first / (float)second;
    lcd.print(total);
    first = 0, second = 0;
    break;
  case 'C':
    total = 0;
    lcd.clear();
    break;
  }
}

long SecondNumber()
{
  while( 1 )
  {
    customKey = customKeypad.getKey();
    if(customKey >= '0' && customKey <= '9')
    {
      second = second * 10 + (customKey - '0');
      lcd.setCursor(1,1); // og: (0,2)
      lcd.print(second);
    }
    if(customKey == '=') break;  //return second;
  }
 return second; 
}