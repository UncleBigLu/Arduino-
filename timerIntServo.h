/*
  My arduino timer interrupt functions.
  This lib let gpio from 2-13 has PWM output ability.
  Interrupt mode used here is the CTC mode.
  If you can not understand the code, please read the AVR datasheet carefully.
*/
#pragma once

#include "pinDefination.h"

// Change the following defination if you need to change the servo num.
#define SERVO_NUM 5
#define SERVO_MAP {SERVO0, SERVO1, SERVO2, SERVO3, HUM_SERVO}

#define PWM_CYCLE_US 20000

bool _PWMChangeFlag = false;
uint16_t _softTCNT2 = 0;
uint8_t _servoMap[SERVO_NUM] = SERVO_MAP;
// Arrays to control the high level pwm time
// Value must be mutiples of 80 
uint16_t _desiredPWMLowPos[SERVO_NUM] = {}; 
uint16_t _internalPWMLowPos[SERVO_NUM] = {};

// Must be called before using the lib
// This func blocks analogWrite() at pin3 and pin11
// since it set timer2 at CTC mode
void initPWM();
ISR(TIMER2_COMPA_vect);
// Param lowPos must be mutiples of 80
bool updatePWM(const uint8_t &index, const uint16_t &lowPos);
// Robotic arm control function
void San_Diego();
