class GameObjects {
  private:
      void racecar(int position){
      lcd.setCursor(2, position);
      lcd.printByte(1);
      lcd.printByte(2);
    }
  public:
    void player(char key){
      if (key == '2'){
        racecar(0);
        lcd.setCursor(2, 1);
        lcd.print("  ");
        // return carPosition = 0;
      } else if (key == '8'){
        racecar(1);
        lcd.setCursor(2, 0);
        lcd.print("  ");
        // return carPosition = 1;
      }
    }

    void enemy(int enemyPosition, long time){
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

    void lives(){

    }


};


class Bullet {
  public:
    bulletMovement(){

    }

    bulletCollision(){

    }
}




VerticalObjects vertObj; // Create an instance of the UserInput class

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
}








