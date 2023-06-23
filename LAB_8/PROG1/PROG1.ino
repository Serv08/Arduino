#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

// PEACE
uint8_t peaceLeft[8] = {0x00,0x00,0x01,0x01,0x01,0x01,0x00,0x00};
uint8_t peaceMid[8] = {0x0E,0x15,0x04,0x04,0x04,0x0A,0x11,0x0E};
uint8_t peaceRight[8] = {0x00,0x00,0x10,0x10,0x10,0x10,0x00,0x00};

// HEART
uint8_t heartLeft[8] = {0x06,0x0F,0x1F,0x1F,0x0F,0x07,0x03,0x01};
uint8_t heartRight[8] = {0x0C,0x1E,0x1F,0x1F,0x1E,0x1C,0x18,0x10};

// CODE
uint8_t codeLeft[8] = {0x02,0x04,0x08,0x10,0x08,0x04,0x02,0x00};
uint8_t codeRight[8] = {0x08,0x04,0x02,0x01,0x02,0x04,0x08,0x00};


void setup() {
  lcd.init();         // initialize the lcd 
  lcd.backlight();
  lcd.clear();

  lcd.createChar(1, peaceLeft);
  lcd.createChar(2, peaceMid);
  lcd.createChar(3, peaceRight);
  lcd.createChar(4, heartLeft);
  lcd.createChar(5, heartRight);
  lcd.createChar(6, codeLeft);
  lcd.createChar(7, codeRight);
  lcd.home();
  
  lcd.setCursor(1, 0);
  lcd.printByte(1);   // PEACE
  lcd.printByte(2);
  lcd.printByte(3);

  lcd.setCursor(7, 0);
  lcd.printByte(4);   // HEART
  lcd.printByte(5);

  lcd.setCursor(12, 0);
  lcd.printByte(6);   // CODE
  lcd.printByte(7);

  lcd.setCursor(0, 1);
  lcd.print("Peace Love Code");
}

void loop() {}
