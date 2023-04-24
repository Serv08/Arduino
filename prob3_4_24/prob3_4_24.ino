void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  do {
    menu();
    Serial.println("Enter your choice (1-4): ");
    while (!Serial.available()); // wait for user input
    String options = Serial.readStringUntil('\n');
    int option = options.toInt();

    if (option == 1) {
      circleArea();
    } else if (option == 2) {
      rectangleArea();
    } else if (option == 3) {
      triangleArea();
    } else if (option == 4) {
      exit();
      break;
    }
  } while (again());
}

void loop() {
  // put your main code here, to run repeatedly:

}

void exit() {
  Serial.println("Program finished...");
}

int again() {
  Serial.println("Do you want to try again (y/N)");
  while (!Serial.available()); // wait for user input
  String option = Serial.readStringUntil('\n');
  
  if (option == "Y" || option == "y") {
    return 1;
  } else {
    return 0;
    exit();

  }
}

void menu () {
  Serial.println("<<<<< Geometry Calculator >>>>>");
  Serial.println(" ");
  Serial.println("1. Calculate the Area of a Circle.");
  Serial.println("2. Calculate the Area of a Rectangle");
  Serial.println("3. Calculate the Area of a Triangle");
  Serial.println("4. Quit");
  Serial.println(" ");
}

float circleArea() {
  float result;

  Serial.print("Enter the radius: ");
  while (!Serial.available()); // wait for user input
  String radiuss = Serial.readStringUntil('\n');
  float radius = radiuss.toFloat();
  Serial.println(radius);

  result = 3.14159 * radius * radius;
  Serial.print("Circle's area is ");
  Serial.println(result);
}

float rectangleArea() {
  float result;

  Serial.print("Enter the length: ");
  while (!Serial.available()); // wait for user input
  String lengths = Serial.readStringUntil('\n');
  float length = lengths.toFloat();
  Serial.println(length);

  Serial.print("Enter the width: ");
  while (!Serial.available()); // wait for user input
  String widths = Serial.readStringUntil('\n');
  float width = widths.toFloat();
  Serial.println(width);

  result = length * width;
  Serial.print("Rectangle's area is ");
  Serial.println(result);
}

float  triangleArea() {
  float result;

  Serial.print("Enter the base: ");
  while (!Serial.available()); // wait for user input
  String bases = Serial.readStringUntil('\n');
  float base = bases.toFloat();
  Serial.println(base);

  Serial.println("Enter the height");
  while (!Serial.available()); // wait for user input
  String heights = Serial.readStringUntil('\n');
  float height = heights.toFloat();

  result = (base * height) / 2;
  Serial.print("Triangle's area is ");
  Serial.println(result);
}