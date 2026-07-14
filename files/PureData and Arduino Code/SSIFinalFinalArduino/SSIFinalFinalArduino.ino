//IMPORTANT: in PureData, the only patches that need to be open are the "arduinotest" and "Test1" patches

// Sensor pins 
const int trigPin1 = 2;
const int echoPin1 = 3;
const int trigPin2 = 4;
const int echoPin2 = 5;
const int trigPin3 = 6;
const int echoPin3 = 7;
const int trigPin4 = 8;
const int echoPin4 = 9;

// Antenna pins
const int antenna1 = 10;
const int antenna2 = 11;
const int antenna3 = 12;
const int antenna4 = 13;

// Potentiometer and motor pins
const int potPin   = A0;   // analog input
const int motorPin = A2;   // digital output

// Motor control state
bool motorRunning = false;
bool motorDone = false;
unsigned long motorStartTime = 0;
const unsigned long motorDuration = 10UL * 600UL; // 6 seconds

// Pot threshold (70% of 0–1023)
const int potThreshold = 0.40 * 1023;



long readUltrasonicDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  return duration * 0.034 / 2;
}

void setup() {
  Serial.begin(9600);

  // Sensor pins
  pinMode(trigPin1, OUTPUT); pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT); pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT); pinMode(echoPin3, INPUT);
  pinMode(trigPin4, OUTPUT); pinMode(echoPin4, INPUT);

  // Antenna pins
  pinMode(antenna1, INPUT_PULLUP);
  pinMode(antenna2, INPUT_PULLUP);
  pinMode(antenna3, INPUT_PULLUP);
  pinMode(antenna4, INPUT_PULLUP);

  //Motor and pot setup
  pinMode(motorPin, OUTPUT);
  digitalWrite(motorPin, LOW);  
  delay(1000);
}

void loop() {
  // Potentiometer check
  int potValue = analogRead(potPin);

  if (!motorRunning && !motorDone && potValue < potThreshold) {
    // start motor
    delay(1000);
    digitalWrite(motorPin, HIGH);
    motorRunning = true;
    motorStartTime = millis();
    motorDone = true;
  }

  if (motorRunning && (millis() - motorStartTime >= motorDuration)) {
    // stop motor
    digitalWrite(motorPin, LOW);
    motorRunning = false;
  }

  //Ultrasonic sensors 
  long distance1 = readUltrasonicDistance(trigPin1, echoPin1);
  long distance2 = readUltrasonicDistance(trigPin2, echoPin2);
  long distance3 = readUltrasonicDistance(trigPin3, echoPin3);
  long distance4 = readUltrasonicDistance(trigPin4, echoPin4);

   if (distance1 >= 150)
    Serial.println("0");
    else if(distance1 <= 150 && distance1 > 110)
      Serial.println("1");
    else if (distance1 <= 110 && distance1 > 70)
      Serial.println("2");
    else if (distance1 <= 70 && distance1 > 30)
      Serial.println("3");
    else if (distance1 <= 30 && distance1 >= 0)
      Serial.println("4");

  delay(10);

  if (distance2 >= 150)
    Serial.println("0");
    else if(distance2 <= 150 && distance2 > 110)
      Serial.println("1");
    else if (distance2 <= 110 && distance2 > 70)
      Serial.println("2");
    else if (distance2 <= 70 && distance2 > 30)
      Serial.println("3");
    else if (distance2 <= 30 && distance2 >= 0)
      Serial.println("4");

  delay(10);

  if (distance3 >= 150)
    Serial.println("0");
    else if(distance3 <= 150 && distance3 > 110)
      Serial.println("1");
    else if (distance3 <= 110 && distance3 > 70)
      Serial.println("2");
    else if (distance3 <= 70 && distance3 > 30)
      Serial.println("3");
    else if (distance3 <= 30 && distance3 >= 0)
      Serial.println("4");
  
  delay(10);

  if (distance4 >= 150)
    Serial.println("0");
    else if(distance4 <= 150 && distance4 > 110)
      Serial.println("1");
    else if (distance4 <= 110 && distance4 > 70)
      Serial.println("2");
    else if (distance4 <= 70 && distance4 > 30)
      Serial.println("3");
    else if (distance4 <= 30 && distance4 >= 0)
      Serial.println("4");


  delay(10);


  //Antenna 1 Death State Check
  int pinState1 = digitalRead(antenna1); 

  if(pinState1 == LOW) {
    Serial.println("a"); // Cable connected (pin connected to ground)
  } else {
    Serial.println("b"); // Cable disconnected
  }

  delay(10);

  //Antenna 2 Death State Check
  int pinState2 = digitalRead(antenna2); // Read the pin state

  if(pinState2 == LOW) {
    Serial.println("c"); // Cable connected (pin connected to ground)
  } else {
    Serial.println("d"); // Cable disconnected
  }

  delay(10);

  //Antenna 3 Death State Check
  int pinState3 = digitalRead(antenna3); // Read the pin state

  if(pinState3 == LOW) {
    Serial.println("e"); // Cable connected (pin connected to ground)
  } else {
    Serial.println("f"); // Cable disconnected
  }

  delay(10);

  //Antenna 4 Death State Check
  int pinState4 = digitalRead(antenna4); // Read the pin state

  if(pinState4 == LOW) {
    Serial.println("g"); // Cable connected (pin connected to ground)
  } else {
    Serial.println("h"); // Cable disconnected
  }

  // Delay between readings (1000 ms = 1 second)
  delay(10);

  Serial.println("-----");

}
