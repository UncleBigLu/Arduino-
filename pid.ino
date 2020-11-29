#include "pid.h"

// A very simple PID loop
// I is not used since P is just enough for this project.
int pid(int data){
  int ret = data * P;
  if(ret > 255)
    ret = 255;
  else if(ret < -255)
    ret = -255;
  return ret;
}
