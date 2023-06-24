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


// HEART
uint8_t heartChar[8] = {0x0,0xa,0x1f,0x1f,0xe,0x4,0x0};

// ENEMY
uint8_t enemyChar[8] = {0x00,0x07,0x05,0x1A,0x0E,0x02,0x06,0x05};

uint8_t bulletChar[8] = {0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00};

// CAR
uint8_t carChar1[8] = {0x00,0x0E,0x0B,0x1F,0x1F,0x0B,0x0E,0x00};
uint8_t carChar2[8] = {0x00,0x1C,0x16,0x1F,0x1F,0x16,0x1C,0x00};

uint8_t emptyChar[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

int topRow = 0;
int botRow = 1;

// int carPosition;
int score = 0;
int life = 3;

int bulletDistance = 9;
int counterForFirstLoop = 0;
int carDeathPoint = 4;


int bulletRowPosition;


long unsigned prevTimeInMillis = 0;
long unsigned prevTime = 0;
long unsigned parentPrevTime = 0;
long unsigned childPrevTime = 0;
bool playAgain;
int scoreCounter = 0;
int bulletSpeedPerFrame = 50;
int carPositionFromKey; 

int lives = 3;


void setup() {
  Serial.begin(9600);
  lcd.init();         // initialize the lcd 
  lcd.backlight();
  lcd.clear();
  lcd.createChar(0, heartChar);
  lcd.createChar(1, carChar1);
  lcd.createChar(2, carChar2);
  lcd.createChar(3, enemyChar);
  lcd.createChar(4, bulletChar);
  lcd.createChar(5, emptyChar);
  racecar(topRow); // only for displa
}

// ###################################################################################################

void loop() {
  // TIME PROCESS
  long timeInMillis = millis();
  long timeInSeconds = timeInMillis /1000;

  // CHANGING VARIABLES PER LOOP
  char key = keypad.getKey(); // checks  keypad input everytime (every loop)
  int enemyRandomPosition = random(0,2); // generates random enemy (and bullet) row position
  int bulletHit = 0;  // bullet column position at deathpoint
  int died = 1;
  
  int enemyBullet = enemy(enemyRandomPosition, timeInMillis);
  // SERIAL DIAGNOSTICS
  Serial.print("|enemyBullet: "); 
  Serial.print(enemyBullet); 


  long parentLoopInterval = 800;
  long childLoopInterval = 200;
  Serial.print(" |bullet movement loop... ");

  // ##################################################################################################################################
  int bulletEndRange = 2;
  for ( int bulletColPos = 14; bulletColPos > bulletEndRange; bulletColPos--){
    lcd.setCursor(bulletColPos, enemyBullet);
    lcd.printByte(4);

    for (int bulletDisplacement = 14; bulletDisplacement > bulletColPos; bulletDisplacement--){ // prints the displacement (" ") of the bullet
      lcd.setCursor(bulletColPos + 1, enemyBullet);
      lcd.print(" ");

      // to move car
      char key = keypad.getKey(); // checks  keypad input everytime (every loop)
      carPositionFromKey = carMovement(key);

      delay(bulletSpeedPerFrame); // + 100ms
    }
    // SERIAL DIAGNOSTICS: prints the value of bullet column position
    Serial.print(" |BulletHit: ");
    Serial.print(bulletHit);
    Serial.print(" |carPositionFromKey: ");
    Serial.print(carPositionFromKey);
    Serial.print(" |EnemyPos: ");
    Serial.println(enemyRandomPosition);

    if ((bulletColPos == carDeathPoint) && (carPositionFromKey == enemyBullet)){
      // deathSound(); // TODO: death sound function
      lives--;
      died = 1;
      Serial.print("  Status: Dead# ");
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
      Serial.print("  Status: Alive ");
    }

    Serial.print("  Lives: ");
    Serial.print(lives);
    
    if (lives == 0){
      Serial.print("\nGAME OVER");
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("GAME  OVER");
      lcd.setCursor(4, 1);
      lcd.print("SCORE: ");
      lcd.print(score);
      delay(5000);
      // while(!key){
      //   lcd.clear();
      //   lcd.print("PRESS ANY KEY ");
      //   lcd.setCursor(0, 1);
      //   lcd.print("TO TRY AGAIN");
      //   delay(5000);
      //   break;
      //   lives = 3;
      //   score = 0;
      //   died = 0;
      // }
    }

    lcd.home();
    lcd.print(lives);
    lcd.write(0);
    lcd.setCursor(0, botRow);
    lcd.print(score);
  }

  // ##################################################################################################################################

  Serial.println();
  Serial.print(" |Died: ");
  Serial.println(died);
  if (died == 0){
    Serial.print("\n |SCORE : ");
    score++;
    Serial.println(score);
  }

  // SERIAL DIAGNOSTICS
  Serial.print(" |CarPosition: ");
  if (carPositionFromKey == 1){
    Serial.print(carPositionFromKey);
    Serial.print("(down)");
  } else {
    Serial.print(carPositionFromKey);
    Serial.print("(uupp)");
  }
  Serial.print(" |bulletRowPosition: ");
  Serial.print(enemyBullet);
  Serial.print(" |enemyPosition: ");
  Serial.print(enemyBullet);
  Serial.print(" |time: ");
  Serial.print(timeInSeconds);
  Serial.println(); // new line
}

// carMovement func: FUNCTION FOR THE MOVEMENT OF THE CAR; returns value of the current car position
int carMovement(char key){
  int carPosition;
  if (key){
    if (key == '2'){
      Serial.println("\n#######################          racecar up            #######################");
      racecar(0);
      lcd.setCursor(2, 1);
      lcd.print("  ");
      return 0;
    } else if (key == '8'){
      Serial.println("\n#######################          racecar down          #######################");
      racecar(1);
      lcd.setCursor(2, 0);
      lcd.print("  ");
      return 1;
    }
  }
}

// racercar func: COSTUMIZED CHARACTER FOR THE CAR
void racecar(int position){
  lcd.setCursor(2, position);
  lcd.printByte(1);
  lcd.printByte(2);
}

// enemy func: FUNCTION FOR ENEMY POSITION; returns the row of the bullet (same with the row of the enemy); uses millis() as delay
int enemy(int enemyPosition, long time){
  long cue = time;
  long interval = 1000;
  if ((cue - prevTime) >= interval){ // TODO: ADJUST THE TELEPORTATION SKILL OF ENEMY GUNNER
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