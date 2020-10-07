#include "pinDefination.h"
void robotRun(int rectify, bool runDirection){
  int lPower = 255;
  int rPower = 255;
  if (rectify > 0)
    rPower -= rectify;
  if (rectify < -0)
    lPower += rectify;
  if(runDirection == true)
  {
    analogWrite(MOTOR_LEFT, lPower);
    analogWrite(MOTOR_RIGHT, rPower);
  }
  else
  {
    digitalWrite(MOTOR_LEFT, LOW);
    digitalWrite(MOTOR_RIGHT, LOW);
    analogWrite(MOTOR_LEFT_BACK, rPower);
    analogWrite(MOTOR_RIGHT_BACK, lPower);
  }
  
}

void robotStop(){
  analogWrite(MOTOR_LEFT, 0);
  analogWrite(MOTOR_RIGHT, 0);
  analogWrite(MOTOR_LEFT_BACK, 0);
  analogWrite(MOTOR_RIGHT_BACK, 0);
}

bool collidDetect(int pin){
  bool state = digitalRead(pin);
  if(state != lastDebounceState)
  {
    lastDebounceTime = millis();
    lastDebounceState = state;
  }
  if(millis() - lastDebounceTime < debounceDelay)
  {
    return lastReadState;
  }
  else
  {
    lastReadState = state;
    return state;
  }
    
}

int humidityDetect(){
  updatePWM(3, 2080);
  delay(2000);
  int ret = 0;
  for(int i = 0; i < 10; ++i)
    ret += analogRead(HUMIDITY);
  ret /= 10;
  updatePWM(3,1040);
  delay(800);
  return ret;
}
