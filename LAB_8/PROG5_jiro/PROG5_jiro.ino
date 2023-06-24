#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

# include <Keypad.h>
const byte ROWS = 4; // Number of rows on the keypad
const byte COLS = 4; // Number of columns on the keypad
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};    // Connect to the row pinouts of the keypad
byte colPins[COLS] = {2, 3, 4, 5};    // Connect to the column pinouts of the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

uint8_t heartChar[8] = {0x0,0xa,0x1f,0x1f,0xe,0x4,0x0};
uint8_t enemyChar[8] = {0x00,0x07,0x05,0x1A,0x0E,0x02,0x06,0x05};
uint8_t bulletChar[8] = {0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00};
uint8_t carChar1[8] = {0x00,0x0E,0x0B,0x1F,0x1F,0x0B,0x0E,0x00};
uint8_t carChar2[8] = {0x00,0x1C,0x16,0x1F,0x1F,0x16,0x1C,0x00};

int topRow = 0;
int botRow = 1;
int score = 0;
int carDeathPoint = 4;
int bulletRowPosition;
long unsigned prevTime = 0;
int bulletSpeedPerFrame = 50;
int carPositionFromKey; 

int lives = 3;

void setup() {
  lcd.init();         // initialize the lcd 
  lcd.backlight();
  lcd.clear();
  lcd.createChar(0, heartChar);lcd.createChar(1, carChar1);
  lcd.createChar(2, carChar2);lcd.createChar(3, enemyChar);
  lcd.createChar(4, bulletChar);
  racecar(topRow); // only for displa
}

void loop() {
  long timeInMillis = millis();
  char key = keypad.getKey(); // checks  keypad input everytime (every loop)
  int enemyRandomPosition = random(0,2); // generates random enemy (and bullet) row position
  int died = 1;
  int enemyBullet = enemy(enemyRandomPosition, timeInMillis);
  int bulletEndRange = 2;

  for ( int bulletColPos = 14; bulletColPos > bulletEndRange; bulletColPos--){
    lcd.setCursor(bulletColPos, enemyBullet);
    lcd.printByte(4);
    for (int bulletDisplacement = 14; bulletDisplacement > bulletColPos; bulletDisplacement--){ 
      lcd.setCursor(bulletColPos + 1, enemyBullet);
      lcd.print(" ");
      // to move car
      char key = keypad.getKey(); // checks  keypad input everytime (every loop)
      carPositionFromKey = carMovement(key);
      delay(bulletSpeedPerFrame); // + 100ms
    }
    if ((bulletColPos == carDeathPoint) && (carPositionFromKey == enemyBullet)){
      // deathSound(); // TODO: death sound function
      lives--;
      died = 1;
      lcd.clear();
      lcd.home();
      lcd.print("  You are hit!");
      lcd.setCursor(2, 1);
      lcd.print(lives);
      lcd.print(" lives left");
      delay(2000);
      lcd.clear();
      racecar(carPositionFromKey);
      break;
    } else {
      if (bulletColPos < carDeathPoint){
        lcd.setCursor(3, enemyBullet);
        lcd.print("  ");
      }
      died = 0;
    }

    if (lives == 0){
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("GAME  OVER");
      lcd.setCursor(4, 1);
      lcd.print("SCORE: ");
      lcd.print(score);
      delay(5000);
    }
    lcd.home();
    lcd.print(lives);
    lcd.write(0);
    lcd.setCursor(0, botRow);
    lcd.print(score);
  }
  if (died == 0){
    score++;
  }
}

int carMovement(char key){
  int carPosition;
  if (key){
    if (key == '2'){
      racecar(0);
      lcd.setCursor(2, 1);
      lcd.print("  ");
      return 0;
    } else if (key == '8'){
      racecar(1);
      lcd.setCursor(2, 0);
      lcd.print("  ");
      return 1;
    }
  }
}

void racecar(int position){
  lcd.setCursor(2, position);
  lcd.printByte(1);
  lcd.printByte(2);
}

int enemy(int enemyPosition, long time){
  long cue = time;
  long interval = 1000;
  if ((cue - prevTime) >= interval){ 
    if (enemyPosition == topRow){
      lcd.setCursor(15, enemyPosition);
      lcd.printByte(3);
      lcd.setCursor(15, 1);
      lcd.print(" ");
    } else if (enemyPosition == botRow){
      lcd.setCursor(15, enemyPosition);
      lcd.printByte(3);
      lcd.setCursor(15, 0);
      lcd.print(" ");
    }
    prevTime = cue;
    return enemyPosition;
  }  
}