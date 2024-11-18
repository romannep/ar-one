#include <math.h>
#include <VarSpeedServo.h>

VarSpeedServo myServo2;  // left leg

VarSpeedServo myServo3;  // left arm

VarSpeedServo myServo4;  // right arm

VarSpeedServo myServo5;  // right leg

VarSpeedServo myServo6;  // left foot

VarSpeedServo myServo7;  // left hand

VarSpeedServo myServo8;  // right hand

VarSpeedServo myServo9;  // right foot

int _init[] = { 150, 200, 20, 45, 90, 90, 90, 90 };
int _state[8];

float _anglePerSecondPerSpeedUnit = 2.4;

VarSpeedServo _getServo(int index) {
  switch (index) {
  case 0:
    return myServo2;
  case 1:
    return myServo3;
  case 2:
    return myServo4;
  case 3:
    return myServo5;
  case 4:
    return myServo6;
  case 5:
    return myServo7;
  case 6:
    return myServo8;
  case 7:
    return myServo9;
  }
}
int _getServoPin(int index) {
  return index + 2;
}
int _getDirection(int index) {
  switch (index) {
  case 0:
    return -1;
  case 1:
    return -1;
  case 2:
    return 1;
  case 3:
    return 1;
  case 4:
    return 1;
  case 5:
    return 1;
  case 6:
    return -1;
  case 7:
    return -1;
  }
}

void _doInit(int index) {
  VarSpeedServo servo = _getServo(index);
  servo.attach(_getServoPin(index));
  servo.slowmove(_state[index], 60);
}

void setup() {

  for (int i = 0; i < 8; i++) {
    VarSpeedServo servo = _getServo(index);
    servo.attach(_getServoPin(index));
    servo.detach();
  }

  for (int i = 0; i < 8; i++) {
    _state[i] = _init[i];
    _doInit(i);
  }

  tone(A3, 1200, 100);
  delay(100);
  tone(A3, 2200, 100);
  delay(100);
  tone(A3, 3200, 100);
  delay(1000);
  Serial.begin(9600);
  pinMode(10, INPUT_PULLUP);
}

int _rightArm = _rightArmInit;
int _leftArm = _leftArmInit;
int _rightHand = _rightHandInit;

void leftArm(int a, int speed) {
  myServo3.slowmove(_leftArmInit - a, speed);
}

void rightArm(int a, int timeMs) {
  int newAngle = _rightArmInit + a;
  int length = abs(_rightArm - newAngle);
  float absSpeed = length * 1000 / timeMs;
  float relSpeed = absSpeed / _anglePerSecondPerSpeedUnit;
  int speed = round(relSpeed);

  myServo4.slowmove(newAngle, speed);
  _rightArm = newAngle;
}


void leftLeg(int a, int speed) {
  myServo2.slowmove(_leftLegInit - a, speed);
}
void rightLeg(int a, int speed) {
  myServo5.slowmove(_rightLegInit + a, speed);
}

void leftFoot(int a, int speed) {
  myServo6.slowmove(_leftFootInit + a, speed);
}
void rightFoot(int a, int speed) {
  myServo9.slowmove(_rightFootInit - a, speed);
}

int tactMs = 1000;

void loop() {

  byte buttonState = digitalRead(10);

  if (buttonState != LOW) {
    return;
  }


  delay(250);

  rightArm(30, 200);
  delay(200);

  delay(800);
  rightArm(0, 200);
  delay(200);

  delay(800);
  rightArm(30, 200);
  delay(200);

  delay(800);
  rightArm(0, 200);
  delay(200);

  delay(800);
  rightArm(30, 200);
  delay(200);

  delay(800);
  rightArm(0, 200);
  delay(200);

  delay(800);
  rightArm(30, 200);
  delay(200);

  delay(800);
  rightArm(0, 200);
  delay(200);

  delay(800);
  rightArm(30, 200);
  delay(200);

  delay(800);
  rightArm(0, 200);
  delay(200);
  delay(800);
  rightArm(30, 200);
  delay(200);

  delay(800);
  rightArm(0, 200);
  delay(200);
}
