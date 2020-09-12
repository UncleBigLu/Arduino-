#include "filter.h"
#include "pinDefination.h"
#include "pid.h"
#include "motor.h"

void setup() {
  Serial.begin(115200);

  pinMode(MOTOR_LEFT, OUTPUT);
  pinMode(MOTOR_RIGHT, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(6,LOW);
  digitalWrite(6,LOW);
  positionOffset = filterInitial();
  Serial.println(positionOffset);
  delay(5000);
}

void loop() {
  int dir = analogRead(IR_LEFT) - analogRead(IR_RIGHT);
  dir = filter(dir) - positionOffset;
  robotRun(pid(dir));
}
