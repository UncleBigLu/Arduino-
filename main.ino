#include "filter.h"
#include "pinDefination.h"
#include "pid.h"
#include "motor.h"
#include "timerIntServo.h"

void setup() {
  // Enable serial debug
  Serial.begin(115200);
  // Initial motors
  pinMode(MOTOR_LEFT, OUTPUT);
  pinMode(MOTOR_RIGHT, OUTPUT);


  // Initial PID
  positionOffset = filterInitial();
  
  // Initial collide detect pins
  pinMode(COLLID_BACK, INPUT);
  stopFlag = true;
  
  // Initial servo timer
  initPWM();
  
  Serial.println(positionOffset);
  delay(5000);
}

void loop() {
  // Control the robot run straightly
  int dir = analogRead(IR_LEFT) - analogRead(IR_RIGHT);
  dir = filter(dir) - positionOffset;
  robotRun(pid(dir));
  
  if( (collidDetect(COLLID_BACK) == 0) && (stopFlag == true) )
  {
    robotStop();
    if (humidityDetect() > 500)
      {
        // water the flower
        digitalWrite(PUMP, HIGH);
        delay(700);
        digitalWrite(PUMP, LOW);
        delay(1500);
        // Fertilize
        San_Diego();
        // Raise the humidity detect arm
        updatePWM(4, 1280);
        delay(1500);
      }
    stopFlag = false;
  }
  if( collidDetect(COLLID_BACK) == 1)
  {
    stopFlag = true;
  }
    
}
