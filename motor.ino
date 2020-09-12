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
