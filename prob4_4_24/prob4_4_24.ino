void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Grades Evaluator");
  Serial.print("Exam1: ");
  while (!Serial.available()); // wait for user input
  String exm1 = Serial.readStringUntil('\n');
  float exam1 = exm1.toFloat();
  Serial.println(exam1);

  Serial.print("Exam2: ");
  while (!Serial.available()); // wait for user input
  String exm2 = Serial.readStringUntil('\n');
  float exam2 = exm2.toFloat();
  Serial.println(exam2);

  Serial.print("Exam3: ");
  while (!Serial.available()); // wait for user input
  String exm3 = Serial.readStringUntil('\n');
  float exam3 = exm3.toFloat();
  Serial.println(exam3);

  Serial.print("Exam4: ");
  while (!Serial.available()); // wait for user input
  String exm4 = Serial.readStringUntil('\n');
  float exam4 = exm4.toFloat();
  Serial.println(exam4);


  float ave = (exam1+exam2+exam3+exam4)/4;

  float arrayGrades[4] = {exam1, exam2, exam3, exam4};

  float lowest = 101;
  for(int i = 0; i<4 ; i++){
    if (arrayGrades[i] < lowest)
        lowest = arrayGrades[i];
  }

  Serial.print("Your lowest score was: ");
  Serial.println(lowest);

  Serial.print("Your exam average is: ");
  Serial.print(ave);
  Serial.println('%');

  Serial.print("Your grade in the course is: ");
  Serial.println(gradeFunc(ave));

  delay(2000); // wait for 2 second before prompting the user again
}

void loop() {
  // put your main code here, to run repeatedly:

}

char gradeFunc(float exam){
   if (exam >= 90)
      return 'A';
   else if (exam >= 80 && exam < 90)
      return 'B';
   else if (exam >= 70 && exam < 80)
      return 'C';
   else if (exam >= 60 && exam < 70)
      return 'D';
   else if (exam < 60)
      return 'E';
}