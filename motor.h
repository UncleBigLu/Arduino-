# pragma once

void robotRun(int rectify);
void robotStop();
bool stopFlag;
// Collid detect functions
uint16_t lastDebounceTime = 0;
uint16_t debounceDelay = 100;
bool lastReadState = true;
bool lastDebounceState = true;
bool collidDetect(int pin);

void pumpDrive();
