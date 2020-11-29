#include "pinDefination.h"
void robotRun(int rectify){
  int lPower = 255;
  int rPower = 255;
  if (rectify > 0)
    rPower -= rectify;
  if (rectify < -0)
    lPower += rectify;;
  analogWrite(MOTOR_LEFT, 2*lPower/3);
  analogWrite(MOTOR_RIGHT, 2*rPower/3);
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

int humidityDetect(){
  // Put down the humidity detect arm
  updatePWM(4, 2240);
  delay(2000);
  int ret = 0;
  for(int i = 0; i < 10; ++i)
    ret += analogRead(HUMIDITY);
  ret /= 10;
 
  return ret;
}
