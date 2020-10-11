#include "filter.h"
#include "pinDefination.h"
#include "pid.h"
#include "motor.h"
#include "timerIntServo.h"

const int flowerPotNum = 4;
int flowerPotCounter = 0;
// True for forward, false for back
bool runDir = true;

void setup() {
  Serial.begin(115200);
  // Initial motors
  pinMode(MOTOR_LEFT, OUTPUT);
  pinMode(MOTOR_RIGHT, OUTPUT);
  pinMode(PUMP, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(6, LOW);
  digitalWrite(10, LOW);
  digitalWrite(PUMP, LOW);
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

int irLeft, irRight;

void loop() {
  // Control the robot run straightly
  if(runDir == true)
  {
    irLeft = IR_LEFT;
    irRight = IR_RIGHT;
  }
  else
  {
    irLeft = IR_LEFT_BACK;
    irRight = IR_RIGHT_BACK;
  }
  int dir = analogRead(irLeft) - analogRead(irRight);
  dir = filter(dir) - positionOffset;
  if(!(flowerPotCounter <= 0 && runDir == false)) 
    robotRun(pid(dir), runDir);

  if (runDir == true)
  {
    // Flower pot detect
    if ( (collidDetect(COLLID_BACK) == 0) && (stopFlag == true) )
    {
      flowerPotCounter++;
      robotStop();
      delay(1500);if(Serial.available())
  {
    
    int x = Serial.parseInt();
    Serial.println(x);
    updatePWM(1,x);
    while(Serial.read() != -1);
    
  }
      if (humidityDetect() > 300)
      {
        // water the flower
        digitalWrite(PUMP, HIGH);
        delay(700);
        digitalWrite(PUMP, LOW);
        delay(1500);
        updatePWM(3,1040);
        delay(1500);
        San_Diego();
      }
      updatePWM(3,1040);
      delay(800);
      stopFlag = false;
    }
    if ( collidDetect(COLLID_BACK) == 1)
    {
      stopFlag = true;
    }
    // Reverse direction
    if(flowerPotCounter >= flowerPotNum)
      runDir = false;
  }
  if(runDir == false)
  {
    if( collidDetect(COLLID_BACK) == 1)
      stopFlag = true;
    if( collidDetect(COLLID_BACK) == 0 && stopFlag == true){
      flowerPotCounter--;
      stopFlag = false;
    }
    if(flowerPotCounter <= 1)
    {
      delay(1000);
      robotStop();
    }
  }

}
