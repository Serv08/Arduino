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
int deathPoint = 2;


int bulletRowPosition;


long prevTimeInMillis = 0;
long prevTimeInSeconds = 0;
long prevTime = 0;

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

  racecar(topRow); // only for display

  // lives remaining
  lcd.home();
  lcd.print("XX");
  // lcd.printByte(7);

  // score
  // lcd.setCursor(0, botRow);
  // lcd.print("--");
}

// ###################################################################################################

void loop() {
  // TIME PROCESS
  long timeInMillis = millis();
  long timeInSeconds = timeInMillis /1000;

  // CHANGING VARIABLES PER LOOP
  char key = keypad.getKey(); // initialization of keypad
  int enemyRandomPosition = random(0,2); 

  // score
  lcd.setCursor(0, botRow);
  lcd.print(timeScore(timeInSeconds));


  int carPositionFromKey = carMovement(key);
  // SERIAL DIAGNOSTICS
  Serial.print("time: ");
  Serial.print(timeInSeconds);


  int enemyBullet = enemy(enemyRandomPosition, timeInMillis);
  // SERIAL DIAGNOSTICS
  Serial.print("\t|enemyBullet: "); // COMMENTOUT (use CTRL + F)
  Serial.print(enemyBullet); // COMMENTOUT (use CTRL + F)


  int bulletCollision = bulletMovement(enemyRandomPosition, carPositionFromKey, timeInMillis);
  // SERIAL DIAGNOSTICS
  Serial.print("\t|bulletColPos: "); 
  Serial.print(bulletCollision); 


  // TODO: CHANGE bulletRowPosition. Should be if (carPosition == bulletRowPosition AFTER (n time bullet traveled))
  // if ((bulletCollision == deathPoint) && (carPositionFromKey == enemyRandomPosition)){
  //   Serial.print("  Status: Dead# ");
  // } else {
  //   Serial.print("  Status: Alive ");
  // }

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
  Serial.print(bulletRowPosition);
  Serial.print(" |enemyPosition: ");
  Serial.print(enemyBullet);
  Serial.println();

  // prevTimeInMillis = timeInMillis;
  // prevTimeInSeconds = timeInSeconds;

}

// carMovement func: FUNCTION FOR THE MOVEMENT OF THE CAR; returns value of the current car position
int carMovement(char key){
  int carPosition;
  if (key){
    if (key == '2'){
      Serial.println("racecar up");
      racecar(0);
      lcd.setCursor(2, 1);
      lcd.print("  ");
      return carPosition = 0;
    } else if (key == '8'){
      Serial.println("racecar down");
      racecar(1);
      lcd.setCursor(2, 0);
      lcd.print("  ");
      return carPosition = 1;
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
  // Serial.println(cue);
  long cue = time;
  long interval = 500;
  if ((cue - prevTime) >= interval){ // TODO: ADJUST THE TELEPORTATION SKILL OF ENEMY GUNNER
    // SERIAL DIAGNOSTICS
    // Serial.print("Time of position change: ");
    // Serial.println(cue);
    // Serial.print("Enemy position: ");
    // Serial.print(enemyPosition);
    if (enemyPosition == topRow){
      lcd.setCursor(15, enemyPosition);
      lcd.printByte(3);
      lcd.setCursor(15, 1);
      lcd.print(" ");
      // return enemyPosition = 0;
    } else if (enemyPosition == botRow){
      lcd.setCursor(15, enemyPosition);
      lcd.printByte(3);
      lcd.setCursor(15, 0);
      lcd.print(" ");
      // return enemyPosition = 1;
    }
    prevTime = cue;
  }  
  return enemyPosition;
}


// bulletMovement func: MOVEMENT OF BULLET PER FRAME: uses marquee effect. Returns Bullet Column position
int bulletMovement(int bulletRowPosition, int carPosition, long currentTime) {
  // Serial.print(" | millis delay... time: ");
  // Serial.print(currentTime*1000);
  int bulletEndRange = 1;
  // if ((currentTime % 2) == 0){
    for ( int bulletColPos = 14; bulletColPos > bulletEndRange; bulletColPos--){
        // int startingTime = currentTime; // time of the nth loop starts
        lcd.setCursor(bulletColPos, bulletRowPosition);
        lcd.printByte(4);

        // SERIAL DIAGNOSTICS
        // Serial.print(" |Parent forloop finished running at: ");
        // Serial.print(currentTime - startingTime);

      // assuming the above code runs <500 ms...... WRONG ASSUMPTION. CODE RUNS IN LESS THAN 150ms
      if((currentTime - prevTime) >= 500){ // every half seconds, bullet moves one column 
        for (int bulletDisplacement = 0; bulletDisplacement < bulletColPos; bulletDisplacement++){ // prints the displacement (" ") of the bullet
          lcd.setCursor(bulletColPos + 1, bulletRowPosition);
          lcd.printByte(" ");
        }
          // SERIAL DIAGNOSTICS
          Serial.print(" |bulletColPos: ");
          Serial.print(bulletColPos);
      //     startingTime = currentTime;
        prevTime = currentTime;
      }

      return bulletColPos;
      
      /* IMPORTANT NOTE:
          Using delay halts the loop and other functions.
          Using lcd.clear() clears all the pixels in the LCS.
          Using these are for test only.
      */
      // delay(50);
      // lcd.clear();
    // }
  }
}

// timeScore func
int timeScore(int time){
  int score = time/2; // score per 2 seconds
  if (score>99)
    score = 99;
  return score;
}

