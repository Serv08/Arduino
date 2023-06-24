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
int carDeathPoint = 3;


int bulletRowPosition;


long unsigned prevTimeInMillis = 0;
long unsigned prevTime = 0;
long unsigned parentPrevTime = 0;
long unsigned childPrevTime = 0;
bool playAgain;
unsigned int carPositionFromKey = 0;


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

  racecar(topRow); // only for display

  // lives remaining
  // lcd.home();
  // lcd.print("XX");
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
  char key = keypad.getKey(); // checks  keypad input everytime (every loop)
  int enemyRandomPosition = random(0,2); // generates random enemy (and bullet) row position
  int bulletHit = 0;  // bullet column position at deathpoint


  // score
  lcd.setCursor(0, botRow);
  lcd.print(timeScore(timeInSeconds));


  int enemyBullet = enemy(enemyRandomPosition, timeInMillis);
  // SERIAL DIAGNOSTICS
  Serial.print("|enemyBullet: "); 
  Serial.print(enemyBullet); 


  long parentLoopInterval = 800;
  long childLoopInterval = 200;
  Serial.print(" |bullet movement loop... ");
  // if((timeInMillis - parentPrevTime) >= parentLoopInterval){ // bullet moves one column; millis acts as delay (millis delay)

  
  int bulletEndRange = 1;
  for ( int bulletColPos = 14; bulletColPos > bulletEndRange; bulletColPos--){
    lcd.setCursor(bulletColPos, enemyBullet);
    lcd.printByte(4);

    // HI, I'M THE PROBLEM, IT'S ME
    for (int bulletDisplacement = 14; bulletDisplacement > bulletColPos; bulletDisplacement--){ // prints the displacement (" ") of the bullet
      // if((timeInMillis - childPrevTime) >= childLoopInterval){ // bullet moves one column; millis acts as delay (millis delay)
        lcd.setCursor(bulletColPos + 1, enemyBullet);
        lcd.print(" ");

        // childPrevTime = timeInMillis;
        delay(200); //function should be here
        carPositionFromKey = carMovement(key);
        Serial.print(" |CarPositionFromKey inside child loop: ");
        Serial.print(carPositionFromKey);
      // }
    }
    if (bulletColPos == 3){
    bulletHit = bulletColPos;
    }
  }


  // SERIAL DIAGNOSTICS: prints the value of bullet column position
  Serial.print(" |BulletHit: ");
  Serial.print(bulletHit);
  // if ((bulletHit == carDeathPoint) && (carPositionFromKey == enemyRandomPosition)){
  //   // lcd.blink();
  //   // delay(1000);
  //   // deathSound(); // todo: death sound function
  //   lives--;
  //   Serial.print("  Status: Dead# ");
  //   lcd.clear();
  //   lcd.home();
  //   lcd.print("  You are hit!");
  //   lcd.setCursor(2, 1);
  //   lcd.print(lives);
  //   lcd.print(" lives left");
  //   delay(1000);
  //   lcd.clear();
  // } else {
  //   Serial.print("  Status: Alive ");
  // }

  Serial.print("  Lives: ");
  Serial.print(lives);
  
  if (lives == 0){
    Serial.println();
    Serial.print("GAME OVER");
    lcd.clear();
    lcd.setCursor(6, 0);
    lcd.print("GAME");
    lcd.setCursor(6, 1);
    lcd.print("OVER");
    while(!Serial.available());
  //   do{
  //     if (!key){
  //       playAgain = false;
  //     } else {
  //       lcd.clear();
  //       lcd.setCursor(3, 0);
  //       lcd.print("DO YOU WANT ");
  //       lcd.print(" TO PLAY AGAIN?");
  //       delay(500);
  //     }
  //   } while (playAgain);
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
      Serial.println("#######################          racecar up            #######################");
      racecar(0);
      lcd.setCursor(2, 1);
      lcd.print("  ");
      return carPosition = 0;
    } else if (key == '8'){
      Serial.println("#######################          racecar down          #######################");
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
  long interval = 1000;
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

    // returns enemyPositin after n time
    return enemyPosition;
  }  
}


// bulletMovement func: MOVEMENT OF BULLET PER FRAME: uses marquee effect. Returns Bullet Column position
// int bulletMovement(int bulletRowPosition, int carPosition, long currentTime) {
//   // Serial.print(" | millis delay... time: ");
//   // Serial.print(currentTime*1000);
//   int bulletEndRange = 1;
//   for ( int bulletColPos = 14; bulletColPos > bulletEndRange; bulletColPos--){
//     lcd.setCursor(bulletColPos, bulletRowPosition);
//     lcd.printByte(4);

//     // HI, I'M THE PROBLEM, IT'S ME
//     if((currentTime - prevTime) >= 500){ // every half seconds, bullet moves one column; acts as delay
//       Serial.print(" |millis delay bullet movement... ");
//       for (int bulletDisplacement = 14; bulletDisplacement > bulletColPos; bulletDisplacement--){ // prints the displacement (" ") of the bullet
//         lcd.setCursor(bulletColPos + 1, bulletRowPosition);
//         lcd.printByte(" ");

//         // SERIAL DIAGNOSTICS: prints the value of bullet column position
//         // Serial.print(" |Child forloop displacement: ");
//         // Serial.print(bulletDisplacement);
//       }
//       prevTime = currentTime;
//     }

//     // SERIAL DIAGNOSTICS: prints the value of bullet column position
//     // Serial.print(" |bulletColPos: ");
//     // Serial.print(bulletColPos);
//     return bulletColPos;
//   }
// }

// timeScore func
int timeScore(int time){
  int score = time/2; // score per 2 seconds
  if (score>99)
    score = 99;
  return score;
}

