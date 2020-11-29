#include "filter.h"


int filterInitial(){
  int data = 0;
  unsigned int overTimeCounter = 0;
   while(queueIndex < QUEUE_LENTH)
  {
    
    data = analogRead(IR_LEFT) - analogRead(IR_RIGHT);
    // Put value into the filter window
    if(data < 200 && data > -200)
      dataQueueInternal[queueIndex++] = data;

    // Over time, stop initial
    if(overTimeCounter++ > 1000)
    {
      while(queueIndex < QUEUE_LENTH)
        dataQueueInternal[queueIndex++] = 10;
    }
  }
  queueIndex = 0;
  return filter(analogRead(IR_LEFT) - analogRead(IR_RIGHT));
}

// Get the average value of the window
int filter(int data){
  dataQueueInternal[queueIndex] = data;
  queueIndex = (queueIndex + 1) % QUEUE_LENTH;
  int sum = 0;
  for(int i = 0; i < QUEUE_LENTH; ++i)
    sum += dataQueueInternal[i];
  return (sum / QUEUE_LENTH);
}
