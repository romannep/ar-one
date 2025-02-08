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

int _init[] = { 150, 175, 45, 45, 90, 90, 90, 90 };
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
      return -1;
    case 6:
      return 1;
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
  int diff = a * _getDirection(index);
  int newAngle = _init[index] + diff;
  int length = abs(_state[index] - newAngle);
  int absSpeed = (long)length * 1000 / timeMs;
  int speed = absSpeed / _anglePerSecondPerSpeedUnit;
  // Serial.println("absSpeed=" + String(absSpeed) + " speed="+String(speed));
  VarSpeedServo servo = _getServo(index);
  servo.slowmove(newAngle, speed > 255 ? 255 : speed);
  _state[index] = newAngle;
}
void _saySpeed(int index, int a, int timeMs) {
  Serial.println("SS i=" + String(index) + " a=" + String(a) + " t=" + String(timeMs) + " init=" + String(_init[index]) + " state=" + String(_state[index]));

  int diff = a * _getDirection(index);
  int newAngle = _init[index] + diff;
  int length = abs(_state[index] - newAngle);
  int absSpeed = (long)length * 1000 / timeMs;
  int speed = absSpeed / _anglePerSecondPerSpeedUnit;

  _state[index] = newAngle;

  Serial.println(" d=" + String(diff) + " n=" + String(newAngle) + " l="
                 + String(length) + " as=" + String(absSpeed) + " rs=" + String(speed));
}


int shortMoveMs = 200;
int tactMs = 1020;
int halfTactMs = tactMs / 2;

void legLeftS(int a) {
  _moveByTime(3, a, shortMoveMs);
}
void armLeftS(int a) {
  _moveByTime(2, a, shortMoveMs);
}
void armRightS(int a) {
  _moveByTime(1, a, shortMoveMs);
}
void legRightS(int a) {
  _moveByTime(0, a, shortMoveMs);
}
void footLeftS(int a) {
  _moveByTime(7, a, shortMoveMs);
}
void handLeftS(int a) {
  _moveByTime(6, a, shortMoveMs);
}
void handRightS(int a) {
  _moveByTime(5, a, shortMoveMs);
}
void footRightS(int a) {
  _moveByTime(4, a, shortMoveMs);
}


void legLeft(int a, int timeMs) {
  _moveByTime(3, a, timeMs);
}
void armLeft(int a, int timeMs) {
  _moveByTime(2, a, timeMs);
}
void armRight(int a, int timeMs) {
  _moveByTime(1, a, timeMs);
}
void legRight(int a, int timeMs) {
  _moveByTime(0, a, timeMs);
}
void footLeft(int a, int timeMs) {
  _moveByTime(7, a, timeMs);
}
void handLeft(int a, int timeMs) {
  _moveByTime(6, a, timeMs);
}
void handRight(int a, int timeMs) {
  _moveByTime(5, a, timeMs);
}
void footRight(int a, int timeMs) {
  _moveByTime(4, a, timeMs);
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

  // tone(A3, 1200, 100);
  // delay(100);
  // tone(A3, 2200, 100);
  // delay(100);
  // tone(A3, 3200, 100);
  delay(1000);
  Serial.begin(9600);
  pinMode(10, INPUT_PULLUP);

  // delay(1000);
  // handRightS(90);
  // handLeftS(90);

  // armRightS(5);
  // armLeftS(90);

  // legLeftS(25);
  // legRightS(25);

  // delay(halfTactMs - shortMoveMs);
}

void move1() {  //short before start

  // footRightS(0);
  footLeftS(0);
  legRightS(0);
  legLeftS(0);
  // handRightS(0);
  // handLeftS(0);
  armRightS(0);
  armLeftS(0);



  handLeft(45, shortMoveMs);
  handRight(45, shortMoveMs);
  footRight(25, shortMoveMs);
  delay(shortMoveMs);

  // ^ tact start 1

  delay(tactMs - shortMoveMs);
  footRight(-25, shortMoveMs);
  footLeft(25, shortMoveMs);
  delay(shortMoveMs);

  // ^ tact start 2

  delay(tactMs - shortMoveMs);
  footRight(0, shortMoveMs);
  footLeft(-25, shortMoveMs);
  handLeft(90, shortMoveMs);
  handRight(90, shortMoveMs);
  delay(shortMoveMs);

  // tact start 3

  delay(tactMs - shortMoveMs);
  footLeft(0, shortMoveMs);
  delay(shortMoveMs);

  // tact start 4

  delay(tactMs - shortMoveMs);
  footRight(-25, shortMoveMs);
  handLeft(45, shortMoveMs);
  handRight(45, shortMoveMs);
  delay(shortMoveMs);

  // tact start 5

  delay(tactMs - shortMoveMs);
  footRight(25, shortMoveMs);
  footLeft(-25, shortMoveMs);
  delay(shortMoveMs);

  // tact border 6

  delay(tactMs - shortMoveMs);

  handLeft(90, shortMoveMs);
  handRight(90, shortMoveMs);
  footLeft(25, shortMoveMs);
  footRight(0, shortMoveMs);

  delay(shortMoveMs);

  // tact border 7

  delay(tactMs - shortMoveMs);
  footLeft(0, shortMoveMs);

  delay(shortMoveMs);

  // tact border 8
}

void move2() {

  footRightS(0);
  footLeftS(0);
  legRightS(25);
  legLeftS(0);
  handRightS(0);
  handLeftS(90);
  armRightS(25);
  armLeftS(0);

  delay(shortMoveMs);

  // tact border 1

  legRightS(0);
  delay(halfTactMs - shortMoveMs - shortMoveMs);
  handRightS(25);
  handLeftS(65);
  delay(shortMoveMs);

  handRightS(0);
  handLeftS(90);

  delay(shortMoveMs);

  // half tact

  handLeft(0, halfTactMs);
  handRight(90, halfTactMs);
  armLeft(25, halfTactMs);
  armRight(0, halfTactMs);

  delay(halfTactMs - shortMoveMs);
  legLeftS(25);
  delay(shortMoveMs);

  // tact border 2

  legLeftS(0);
  delay(halfTactMs - shortMoveMs - shortMoveMs);
  handLeftS(25);
  handRightS(70);
  delay(shortMoveMs);

  handLeftS(0);
  handRightS(90);

  delay(shortMoveMs);

  // half tact

  handRight(0, halfTactMs);
  handLeft(90, halfTactMs);
  armRight(25, halfTactMs);
  armLeft(0, halfTactMs);
  delay(halfTactMs - shortMoveMs);
  legRightS(15);
  delay(shortMoveMs);


  // tact border 3

  legRightS(0);
  delay(halfTactMs - shortMoveMs - shortMoveMs);
  handRightS(25);
  handLeftS(70);
  delay(shortMoveMs);

  handRightS(0);
  handLeftS(90);

  delay(shortMoveMs);

  // half tact

  handLeft(0, tactMs);
  handRight(90, tactMs);
  armLeft(25, tactMs);
  armRight(0, tactMs);

  delay(halfTactMs - shortMoveMs);
  legLeftS(25);
  delay(shortMoveMs);
  legLeftS(0);

  // tact border 4
}

int legSideAngle = 25;

void move3(bool prepareForNext) {

  footRightS(0);
  footLeftS(0);
  legRightS(30);
  legLeftS(0);
  handRightS(90);
  handLeftS(90);
  armRightS(90);
  armLeftS(0);

  delay(shortMoveMs);

  // tact border 1
  delay(halfTactMs);

  armRight(0, halfTactMs - shortMoveMs);
  armLeft(90, halfTactMs - shortMoveMs);
  legRight(0, halfTactMs - shortMoveMs);

  delay(halfTactMs - shortMoveMs);

  armRightS(90);
  armLeftS(0);
  legRightS(30);

  delay(shortMoveMs);

  // tact border 2

  armRight(0, halfTactMs - shortMoveMs);
  armLeft(90, halfTactMs - shortMoveMs);
  legRight(0, halfTactMs - shortMoveMs);

  delay(halfTactMs - shortMoveMs);

  armRightS(90);
  armLeftS(0);
  legRightS(30);

  delay(shortMoveMs);

  armRight(0, halfTactMs - shortMoveMs);
  armLeft(90, halfTactMs - shortMoveMs);
  legRight(0, halfTactMs - shortMoveMs);

  delay(halfTactMs - shortMoveMs);

  armRightS(90);
  armLeftS(0);
  legRightS(30);

  delay(shortMoveMs);

  // tact border 3
  delay(halfTactMs);

  armRight(0, halfTactMs - shortMoveMs);
  armLeft(90, halfTactMs - shortMoveMs);
  legRight(0, halfTactMs - shortMoveMs);

  delay(halfTactMs - shortMoveMs);

  armRightS(90);
  armLeftS(0);
  legRightS(30);

  delay(shortMoveMs);

  // tact border 4

  armRight(0, halfTactMs - shortMoveMs);
  armLeft(90, halfTactMs - shortMoveMs);
  legRight(0, halfTactMs - shortMoveMs);

  delay(halfTactMs - shortMoveMs);

  armRightS(90);
  armLeftS(0);
  legRightS(30);

  delay(shortMoveMs);

  armRight(0, halfTactMs - shortMoveMs);
  armLeft(90, halfTactMs - shortMoveMs);
  legRight(0, halfTactMs - shortMoveMs);

  delay(halfTactMs - shortMoveMs);

  armRightS(90);
  armLeftS(0);
  legRightS(30);

  delay(shortMoveMs);

  // repeat
  // tact border 1
  delay(halfTactMs);

  armRight(0, halfTactMs - shortMoveMs);
  armLeft(90, halfTactMs - shortMoveMs);
  legRight(0, halfTactMs - shortMoveMs);

  delay(halfTactMs - shortMoveMs);

  armRightS(90);
  armLeftS(0);
  legRightS(30);

  delay(shortMoveMs);

  // tact border 2

  armRight(0, halfTactMs - shortMoveMs);
  armLeft(90, halfTactMs - shortMoveMs);
  legRight(0, halfTactMs - shortMoveMs);

  delay(halfTactMs - shortMoveMs);

  armRightS(90);
  armLeftS(0);
  legRightS(30);

  delay(shortMoveMs);

  armRight(0, halfTactMs - shortMoveMs);
  armLeft(90, halfTactMs - shortMoveMs);
  legRight(0, halfTactMs - shortMoveMs);

  delay(halfTactMs - shortMoveMs);

  armRightS(90);
  armLeftS(0);
  legRightS(30);

  delay(shortMoveMs);

  // tact border 3

  armRightS(0);
  armLeftS(30);
  footLeft(-45, halfTactMs);

  handLeft(40, halfTactMs / 2);
  handRight(0, halfTactMs / 2);
  delay(halfTactMs / 2);

  handLeft(0, halfTactMs / 2);
  handRight(40, halfTactMs / 2);
  delay(halfTactMs / 2);

  footLeft(0, halfTactMs);
  armLeftS(0);

  handLeft(40, halfTactMs / 2);
  handRight(0, halfTactMs / 2);
  delay(halfTactMs / 2);

  handLeft(0, halfTactMs / 2);
  handRight(40, halfTactMs / 2);
  delay(halfTactMs / 2);

  // tact border 4

  armRightS(30);
  footRight(-45, halfTactMs);

  handLeft(40, halfTactMs / 2);
  handRight(0, halfTactMs / 2);
  delay(halfTactMs / 2);

  handLeft(0, halfTactMs / 2);
  handRight(40, halfTactMs / 2);
  delay(halfTactMs / 2);

  footRight(0, halfTactMs);
  armRightS(0);


  if (prepareForNext) {
    delay(halfTactMs - shortMoveMs);
    handRightS(90);
    handLeftS(90);

    armRightS(25);
    armLeftS(60);

    legLeftS(legSideAngle);
    legRightS(legSideAngle);
    delay(shortMoveMs);
    // // now right position
  } else {
    handLeft(40, halfTactMs / 2);
    handRight(0, halfTactMs / 2);
    delay(halfTactMs / 2);

    handLeft(0, halfTactMs / 2);
    handRight(40, halfTactMs / 2);
    delay(halfTactMs / 2);
  }
}

void move4(bool prepareForNext) {

  // one

  footRightS(0);
  footLeftS(0);
  // legRightS(0);
  // legLeftS(0);
  // handRightS(0);
  // handLeftS(0);
  // armRightS(0);
  // armLeftS(0);

  // delay(halfTactMs - shortMoveMs);
  // handRightS(90);
  // handLeftS(90);

  // armRightS(25);
  // armLeftS(60);

  // legRightS(25);
  // delay(shortMoveMs);
  // // now right position

  delay(halfTactMs - shortMoveMs);

  armRightS(45);
  armLeftS(45);

  legLeftS(0);
  delay(shortMoveMs);
  // now middle position
  // ...and

  delay(halfTactMs - shortMoveMs);
  armRightS(90);
  armLeftS(5);

  legLeftS(legSideAngle);
  delay(shortMoveMs);
  // now left position
  // two

  delay(halfTactMs - shortMoveMs);
  armRightS(45);
  armLeftS(45);

  legRightS(0);
  delay(shortMoveMs);
  // now middle
  // ...and


  delay(halfTactMs - shortMoveMs);
  armRightS(0);
  armLeftS(0);
  handRightS(45);
  handLeftS(-45);

  legRightS(legSideAngle);
  delay(shortMoveMs);
  // now right
  // three

  delay(halfTactMs - shortMoveMs);
  armRightS(15);
  armLeftS(15);
  handRightS(0);
  handLeftS(0);

  legLeftS(0);
  delay(shortMoveMs);
  // now middle
  // ...and

  delay(halfTactMs - shortMoveMs);
  armRightS(0);
  armLeftS(0);
  handRightS(-45);
  handLeftS(45);

  legLeftS(legSideAngle);
  delay(shortMoveMs);
  // now left
  // four

  delay(halfTactMs - shortMoveMs);
  armRightS(15);
  armLeftS(15);
  handRightS(0);
  handLeftS(0);

  legRightS(0);
  delay(shortMoveMs);
  // now middle
  // ...and

  // Repeat

  delay(halfTactMs - shortMoveMs);
  handRightS(90);
  handLeftS(90);

  armRightS(29);
  armLeftS(60);

  legRightS(legSideAngle);
  delay(shortMoveMs);
  // now right position
  // one

  delay(halfTactMs - shortMoveMs);

  armRightS(45);
  armLeftS(45);

  legLeftS(0);
  delay(shortMoveMs);
  // now middle position
  // ...and

  delay(halfTactMs - shortMoveMs);
  armRightS(60);
  armLeftS(25);

  legLeftS(legSideAngle);
  delay(shortMoveMs);
  // now left position
  // two

  delay(halfTactMs - shortMoveMs);
  armRightS(45);
  armLeftS(45);

  legRightS(0);
  delay(shortMoveMs);
  // now middle

  // ...and

  delay(halfTactMs - shortMoveMs);
  handRightS(90);
  handLeftS(90);

  armRightS(29);
  armLeftS(60);

  legRightS(legSideAngle);
  delay(shortMoveMs);
  // now right position
  // three

  armRightS(0);
  armLeftS(30);
  footLeft(-45, halfTactMs);

  handLeft(40, halfTactMs / 2);
  handRight(0, halfTactMs / 2);
  delay(halfTactMs / 2);

  handLeft(0, halfTactMs / 2);
  handRight(40, halfTactMs / 2);
  // legRight(25, halfTactMs / 2);

  delay(halfTactMs / 2);
  // ...and

  footLeft(0, halfTactMs);
  armLeftS(0);

  handLeft(40, halfTactMs / 2);
  handRight(0, halfTactMs / 2);
  delay(halfTactMs / 2);

  handLeft(0, halfTactMs / 2);
  handRight(40, halfTactMs / 2);
  delay(halfTactMs / 2);

  // four

  armRightS(30);
  footRight(-45, halfTactMs);

  handLeft(40, halfTactMs / 2);
  handRight(0, halfTactMs / 2);
  delay(halfTactMs / 2);

  handLeft(0, halfTactMs / 2);
  handRight(40, halfTactMs / 2);
  delay(halfTactMs / 2);

  // ...and

  if (prepareForNext) {
    legLeft(0, halfTactMs / 2);
    armLeft(0, halfTactMs / 2);
    footLeft(0, halfTactMs / 2);
    footRight(0, halfTactMs / 2);
    handLeft(0, halfTactMs / 2);

    delay(halfTactMs - shortMoveMs);

    legRightS(35);
    handRightS(0);
    armRightS(110);
    delay(shortMoveMs);
  } else {
    // handLeft(0, halfTactMs / 2);
    // handRight(40, halfTactMs / 2);


    footRight(0, halfTactMs);
    armRightS(0);

    delay(halfTactMs - shortMoveMs);
    handRightS(90);
    handLeftS(90);

    armRightS(25);
    armLeftS(60);

    legLeftS(legSideAngle);
    legRightS(legSideAngle);
    delay(shortMoveMs);
  }

  // one
}

void move5(bool prepareForNext) {

  // one

  legRight(0, halfTactMs);
  delay(halfTactMs);

  // ...and

  handLeft(35, halfTactMs - shortMoveMs);
  delay(halfTactMs - shortMoveMs);

  legLeftS(35);
  armLeftS(80);
  handLeftS(0);
  delay(shortMoveMs);

  //two

  legLeft(0, halfTactMs);
  delay(halfTactMs);

  // ...and

  handRight(35, halfTactMs - shortMoveMs);
  delay(halfTactMs - shortMoveMs);

  legRightS(35);
  armRightS(0);
  handRightS(0);
  delay(shortMoveMs);

  //three

  legRight(0, halfTactMs);
  delay(halfTactMs);

  // ...and

  handLeft(35, halfTactMs - shortMoveMs);
  delay(halfTactMs - shortMoveMs);

  legLeftS(35);
  armLeftS(0);
  handLeftS(0);
  delay(shortMoveMs);

  // four

  legLeft(0, halfTactMs);
  delay(halfTactMs);

  // ...and

  if (prepareForNext) {
    armLeft(80, halfTactMs * 3);
    armRight(90, halfTactMs * 3);
    delay(halfTactMs);
  } else {
    handRight(35, halfTactMs - shortMoveMs);
    delay(halfTactMs - shortMoveMs);

    legRightS(35);
    armRightS(90);
    handRightS(0);
    delay(shortMoveMs);
  }

  // one
}

void move6(bool prepareForNext) {

  int dl = 20;
  int dr = -30;
  int dll = 30;
  int dlr = 0;
  if (prepareForNext) {
    dl = -30;
    dr = 20;
    dll = 0;
    dlr = 30;
  }
  // one
  delay(halfTactMs);

  // ...and

  delay(halfTactMs - shortMoveMs);
  handLeftS(-45);
  handRightS(-45);
  armLeft(60, halfTactMs);
  armRight(60, halfTactMs);

  delay(shortMoveMs);

  // two

  delay(halfTactMs);

  // ...and

  legLeft(dll, halfTactMs / 2);
  legRight(dlr, halfTactMs / 2);
  delay(halfTactMs / 2);

  armLeft(60 + dl, halfTactMs / 2);
  armRight(60 + dr, halfTactMs / 2);
  delay(halfTactMs / 2);

  // three

  legLeft(0, halfTactMs / 2);
  legRight(0, halfTactMs / 2);
  delay(halfTactMs / 2);

  armLeft(60, halfTactMs / 2);
  armRight(60, halfTactMs / 2);
  delay(halfTactMs / 2);

  // ...and

  legLeft(dll, halfTactMs / 2);
  legRight(dlr, halfTactMs / 2);
  delay(halfTactMs / 2);

  armLeft(70 + dl, halfTactMs / 2);
  armRight(70 + dr, halfTactMs / 2);
  delay(halfTactMs / 2);

  // four
  legLeft(0, halfTactMs / 2);
  legRight(0, halfTactMs / 2);
  delay(halfTactMs / 2);

  armLeft(60, halfTactMs / 2);
  armRight(60, halfTactMs / 2);
  delay(halfTactMs / 2);

  // ...and

  if (prepareForNext) {
    armLeft(0, halfTactMs);
    //armRight(0, halfTactMs);
    delay(halfTactMs);
  } else {
    armLeft(0, halfTactMs);
    armRight(0, halfTactMs);
    delay(halfTactMs);

    armLeft(60, halfTactMs * 2);
    armRight(60, halfTactMs * 2);
  }
}

void loop() {

  byte buttonState = digitalRead(10);
  // Serial.println("tact = " + String(tactMs) + " halfTact = " + String(halfTactMs));

  if (buttonState != LOW) {
    return;
  }

  delay(tactMs * 2 + halfTactMs);

  //
  move1();
  delay(tactMs - shortMoveMs);
  move2();
  delay(tactMs - shortMoveMs);
  move2();
  delay(tactMs - shortMoveMs);
  move1();
  delay(tactMs - shortMoveMs);
  move2();
  delay(tactMs - shortMoveMs);
  move2();
  delay(tactMs - shortMoveMs);
  move3(false);
  move3(true);
  move4(false);
  move4(true);
  move5(false);
  move5(true);
  move6(false);
  move6(true);
  move3(false);
  move3(true);
}
