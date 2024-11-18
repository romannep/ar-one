#include <math.h>
#include <VarSpeedServo.h>

VarSpeedServo myServo2;  // left leg [0]

VarSpeedServo myServo3;  // left arm [1]

VarSpeedServo myServo4;  // right arm [2]

VarSpeedServo myServo5;  // right leg [3]

VarSpeedServo myServo6;  // left foot [4]

VarSpeedServo myServo7;  // left hand [5]

VarSpeedServo myServo8;  // right hand [6]

VarSpeedServo myServo9;  // right foot [7]

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

void _moveByTime(int index, int a, int timeMs) {

  int newAngle = _init[index] + a;
  int length = abs(_state[index] - newAngle);
  float absSpeed = length * 1000 / timeMs;
  float relSpeed = absSpeed / _anglePerSecondPerSpeedUnit;
  int speed = round(relSpeed);

  VarSpeedServo servo = _getServo(index);
  servo.slowmove(newAngle, speed);
  _state[index] = newAngle;
}

void leftLeg(int a, int timeMs) {
  _moveByTime(0, a, timeMs);
}
void leftArm(int a, int timeMs) {
  _moveByTime(1, a, timeMs);
}
void rightArm(int a, int timeMs) {
  _moveByTime(2, a, timeMs);
}
void rightLeg(int a, int timeMs) {
  _moveByTime(3, a, timeMs);
}
void leftFoot(int a, int timeMs) {
  _moveByTime(4, a, timeMs);
}
void leftHand(int a, int timeMs) {
  _moveByTime(5, a, timeMs);
}
void rightHand(int a, int timeMs) {
  _moveByTime(6, a, timeMs);
}
void rightFoot(int a, int timeMs) {
  _moveByTime(7, a, timeMs);
}


void setup() {

  for (int i = 0; i < 8; i++) {
    VarSpeedServo servo = _getServo(i);
    servo.attach(_getServoPin(i));
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

int tactMs = 1000;

void loop() {

  byte buttonState = digitalRead(10);

  if (buttonState != LOW) {
    return;
  }


  delay(250);

  int shortMoveMs = 200;

  rightArm(30, shortMoveMs);
  delay(shortMoveMs);
  
  // tact border

  delay(tactMs - shortMoveMs);
  rightArm(0, shortMoveMs);
  delay(shortMoveMs);

  // tact border

  delay(tactMs - shortMoveMs);
  rightArm(30, shortMoveMs);
  delay(shortMoveMs);

  // tact border

  delay(tactMs - shortMoveMs);
  rightArm(0, shortMoveMs);
  delay(shortMoveMs);

  // tact border

  delay(tactMs - shortMoveMs);
  rightArm(30, shortMoveMs);
  delay(shortMoveMs);

  // tact border
  delay(tactMs - shortMoveMs);
  rightArm(0, shortMoveMs);
  delay(shortMoveMs);

  // tact border

  delay(tactMs - shortMoveMs);
  rightArm(30, shortMoveMs);
  delay(shortMoveMs);

  // tact border

  delay(tactMs - shortMoveMs);
  rightArm(0, shortMoveMs);
  delay(shortMoveMs);

  // tact border
}
