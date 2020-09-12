#ifndef _FILTER_H
#define _FILTER_H
 
#define QUEUE_LENTH 8

uint8_t queueIndex = 0;
int dataQueueInternal[QUEUE_LENTH];
int positionOffset = 0;

int filterInitial(); 
int filter(int data);

#endif
