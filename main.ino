#include "filter.h"
#include "pinDefination.h"
#include "pid.h"
#include "motor.h"
#include "timerIntServo.h"

void setup() {
  Serial.begin(115200);
  // Initial motors
  pinMode(MOTOR_LEFT, OUTPUT);
  pinMode(MOTOR_RIGHT, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(6,LOW);
  digitalWrite(10,LOW);
  // Initial PID
  positionOffset = filterInitial();
  // Initial servo timer
  initPWM();
  
  Serial.println(positionOffset);
 // delay(5000);
}

void loop() {
  // Control the robot run straightly
//  int dir = analogRead(IR_LEFT) - analogRead(IR_RIGHT);
//  dir = filter(dir) - positionOffset;
//  robotRun(pid(dir));
//  
  San_Diego();
  
}
