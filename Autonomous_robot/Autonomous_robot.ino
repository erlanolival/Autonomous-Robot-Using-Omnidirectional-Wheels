const int frontEchoPin = 7;
const int frontTriggerPin = 6;
const int leftEchoPin = 11;
const int leftTriggerPin = 10;
const int rightEchoPin = 9;
const int rightTriggerPin = 8;
const int lrightTriggerPin = 22;
const int lrightEchoPin = 23;
const int lleftTriggerPin = 24;
const int lleftEchoPin = 25;
//first left wheel
const int motorL1P = 52;
const int motorL1N = 53;
//seceond left wheel
const int motorL2P = 54;
const int motorL2N = 55;
//first right wheel
const int motorR1P = 52;
const int motorR1N = 53;
//second right wheel
const int motorR2P = 54;
const int motorR2N = 55;
volatile float maxFrontDistance = 25.00;
volatile float frontDuration, frontDistanceCm, leftDuration, leftDistanceCm, rightDuration, rightDistanceCm,lleftDuration, lleftDistanceCm, lrightDuration, lrightDistanceCm;
volatile float maxLeftDistance, maxRightDistance = 20.00;
volatile float maxLeftLateral, maxRightLateral = 10;
void setup() {
  // serial
  Serial.begin(9600);
  // ultrasonic
  pinMode(frontTriggerPin, OUTPUT);
  pinMode(frontEchoPin, INPUT);
  pinMode(leftTriggerPin, OUTPUT);
  pinMode(leftEchoPin, INPUT);
  pinMode(rightTriggerPin, OUTPUT);
  pinMode(rightEchoPin, INPUT);
  pinMode(lrightTriggerPin, OUTPUT);
  pinMode(lrightEchoPin, INPUT);
  pinMode(lleftTriggerPin, OUTPUT);
  pinMode(lleftEchoPin, INPUT);
  // motors
  pinMode(motorL1P, OUTPUT);
  pinMode(motorL1N, OUTPUT);
  pinMode(motorL2P, OUTPUT);
  pinMode(motorL2N, OUTPUT);
  pinMode(motorR1P, OUTPUT);
  pinMode(motorR1N, OUTPUT);
  pinMode(motorR2P, OUTPUT);
  pinMode(motorR2N, OUTPUT);
}
void loop() {
  // front distance check
  checkFrontDistance();
  if (frontDistanceCm < maxFrontDistance) {
    Serial.println("Too close");
    checkLeftDistance();
    delay(20);
    checkRightDistance();
    delay(20);
    checkLateralRight();
    delay(20);
    checkLateralLeft();
    delay(20);
    if (lleftDistanceCm<maxLeftLateral)
      moveLeftLateral();
    else if (lrightDistanceCm<maxRightLateral)
      moveRightLateral();
      else if (leftDistanceCm < rightDistanceCm)
        moveRight();
        else if (leftDistanceCm > rightDistanceCm) {
          moveLeft();
    }
  }
  else {
    Serial.println("OK");
    moveForward();
  }
  // left distance check
  checkLeftDistance();
  if (leftDistanceCm < maxLeftDistance) {
    Serial.println("Left too close");
    delay(20);
    checkLeftDistance();
    delay(20);
    checkRightDistance();
    delay(20);
    if (leftDistanceCm > rightDistanceCm)
      moveForward();
    else if (leftDistanceCm < rightDistanceCm) {
      moveRight();
    }
  }
  // right distance check
  checkRightDistance();
  if (rightDistanceCm < maxRightDistance) {
    Serial.println("Right too close");
    delay(20);
    checkRightDistance();
    delay(20);
    checkLeftDistance();
    delay(20);
    if (rightDistanceCm > leftDistanceCm)
      moveForward();
    else if (rightDistanceCm < leftDistanceCm) {
      moveLeft();
    }
  }
  // Lateral left distance check
  checkLateralLeft();
  if (lleftDistanceCm < maxLeftLateral) {
    Serial.println("Lateral Right too close");
    delay(20);
    moveLeftLateral();
    delay(20);
  }
  // Lateral right distance check
  checkLateralRight();
  if (lrightDistanceCm < maxRightLateral) {
    Serial.println("Lateral Right too close");
    delay(20);
    moveRightLateral();
    delay(20);
  }
}
void checkFrontDistance() {
  digitalWrite(frontTriggerPin, LOW);  //to generate a clear pulse, we put in LOW 4us
  delayMicroseconds(4);
  digitalWrite(frontTriggerPin, HIGH);  //we generate a trigger of 10us
  delayMicroseconds(10);
  digitalWrite(frontTriggerPin, LOW);
  frontDuration = pulseIn(frontEchoPin, HIGH);  //Measuring the pulse, en microsegundos
  frontDistanceCm = frontDuration * 10 / 292 / 2;  //Converting the distance, in cm
  Serial.print("Distance: ");
  Serial.print(frontDistanceCm);
  Serial.println(" cm");
}
void checkLeftDistance() {
  digitalWrite(leftTriggerPin, LOW);  //to generate a clear pulse, we put in LOW 4us
  delayMicroseconds(4);
  digitalWrite(leftTriggerPin, HIGH);  //we generate a trigger of 10us
  delayMicroseconds(10);
  digitalWrite(leftTriggerPin, LOW);
  leftDuration = pulseIn(leftEchoPin, HIGH);  //Measuring the pulse, en microsegundos
  leftDistanceCm = leftDuration * 10 / 292 / 2;  //Converting the distance, in cm
  Serial.print("Left distance: ");
  Serial.print(leftDistanceCm);
  Serial.println(" cm");
}
void checkRightDistance() {
  digitalWrite(rightTriggerPin, LOW);  //
  delayMicroseconds(4);
  digitalWrite(rightTriggerPin, HIGH);  //
  delayMicroseconds(10);
  digitalWrite(rightTriggerPin, LOW);
  rightDuration = pulseIn(rightEchoPin, HIGH);  //
  rightDistanceCm = rightDuration * 10 / 292 / 2;  //
  Serial.print("Right distance: ");
  Serial.print(rightDistanceCm);
  Serial.println(" cm");
}
void checkLateralLeft() {
  digitalWrite(lleftTriggerPin, LOW); 
  delayMicroseconds(4);
  digitalWrite(lleftTriggerPin, HIGH);  
  delayMicroseconds(10);
  digitalWrite(lleftTriggerPin, LOW);
  lleftDuration = pulseIn(lleftEchoPin, HIGH);  
  lleftDistanceCm = lleftDuration * 10 / 292 / 2; 
  Serial.print("Lateral sensor at Left detected: ");
  Serial.print(lleftDistanceCm);
  Serial.println(" cm");
}
void checkLateralRight() {
  digitalWrite(lrightTriggerPin, LOW);  
  delayMicroseconds(4);
  digitalWrite(lrightTriggerPin, HIGH);  
  delayMicroseconds(10);
  digitalWrite(lrightTriggerPin, LOW);
  lrightDuration = pulseIn(lrightEchoPin, HIGH);  
  lrightDistanceCm = lrightDuration * 10 / 292 / 2;  
  Serial.print("Lateral sensor at Right detected: ");
  Serial.print(lrightDistanceCm);
  Serial.println(" cm");
}
void moveBackward() {
  Serial.println("Backward.");
  digitalWrite(motorL1P, HIGH);
  digitalWrite(motorL1N, LOW);
  digitalWrite(motorL2P, HIGH);
  digitalWrite(motorL2N, LOW);
  digitalWrite(motorR1P, HIGH);
  digitalWrite(motorR1N, LOW);
  digitalWrite(motorR2P, HIGH);
  digitalWrite(motorR2N, LOW);
}
void moveForward() {
  Serial.println("Forward.");
  digitalWrite(motorL1P, LOW);
  digitalWrite(motorL1N, HIGH);
  digitalWrite(motorL2P, LOW);
  digitalWrite(motorL2N, HIGH);
  digitalWrite(motorR1P, LOW);
  digitalWrite(motorR1N, HIGH);
  digitalWrite(motorR2P, LOW);
  digitalWrite(motorR2N, HIGH);
}
void moveLeft() {
  Serial.println("Left.");
  digitalWrite(motorL1P, LOW);
  digitalWrite(motorL1N, HIGH);
  digitalWrite(motorL2P, LOW);
  digitalWrite(motorL2N, HIGH);
  digitalWrite(motorR1P, HIGH);
  digitalWrite(motorR1N, LOW);
  digitalWrite(motorR2P, HIGH);
  digitalWrite(motorR2N, LOW);
}
void moveRight() {
  Serial.println("Right.");
  digitalWrite(motorL1P, HIGH);
  digitalWrite(motorL1N, LOW);
  digitalWrite(motorL2P, HIGH);
  digitalWrite(motorL2N, LOW);
  digitalWrite(motorR1P, LOW);
  digitalWrite(motorR1N, HIGH);
  digitalWrite(motorR2P, LOW);
  digitalWrite(motorR2N, HIGH);
}
void moveLeftLateral() {
  Serial.println("Left.");
  digitalWrite(motorL1P, LOW);
  digitalWrite(motorL1N, HIGH);
  digitalWrite(motorL2P, HIGH);
  digitalWrite(motorL2N, LOW);
  digitalWrite(motorR1P, HIGH);
  digitalWrite(motorR1N, LOW);
  digitalWrite(motorR2P, LOW);
  digitalWrite(motorR2N, HIGH);
}
void moveRightLateral() {
  Serial.println("Right.");
  digitalWrite(motorL1P, HIGH);
  digitalWrite(motorL1N, LOW);
  digitalWrite(motorL2P, LOW);
  digitalWrite(motorL2N, HIGH);
  digitalWrite(motorR1P, LOW);
  digitalWrite(motorR1N, HIGH);
  digitalWrite(motorR2P, HIGH);
  digitalWrite(motorR2N, LOW);
}
