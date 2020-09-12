#include "pid.h"

int pid(int data){
  int ret = data * P;
  if(ret > 255)
    ret = 255;
  else if(ret < -255)
    ret = -255;
  return ret;
}
