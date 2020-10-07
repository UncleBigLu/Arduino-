#include "pinDefination.h"
void robotRun(int rectify){
  int lPower = 255;
  int rPower = 255;
  if (rectify > 0)
    rPower -= rectify;
  if (rectify < -0)
    lPower += rectify;;
  analogWrite(MOTOR_LEFT, lPower);
  analogWrite(MOTOR_RIGHT, rPower);
}

void robotStop(){
  analogWrite(MOTOR_LEFT, 0);
  analogWrite(MOTOR_RIGHT, 1);
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
