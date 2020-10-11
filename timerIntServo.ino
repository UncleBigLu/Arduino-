void initPWM(){
  // Initial timer2 registers
  // Disable global interrupts
  cli();
  // Set the entire Timer/Counter control reginsters to zero
  TCCR2A = 0;
  TCCR2B = 0;
  // Initialize counter value to zero
  TCNT2 = 0;
  // Set prescaler = 128;
  TCCR2B |= (1 << CS22) | (1 << CS20);
  // Turn on CTC mode
  TCCR2A |= (1 << WGM21);
  // Set the compare register for 80 us cycle interrupt
  OCR2A = 9;
  // Enable timer compare A interrupt
  TIMSK2 |= (1 << OCIE2A);
  // Enable global interrupts
  sei();

  // Initial servo pins to output mode
  for(int i = 0; i < SERVO_NUM; ++i)
  {
    pinMode(_servoMap[i], OUTPUT);
  }
  // Initial PWMLowPos arrays
  memset(_desiredPWMLowPos, 0x00, sizeof(_desiredPWMLowPos));
  memset(_internalPWMLowPos, 0x00, sizeof(_internalPWMLowPos));
}

ISR(TIMER2_COMPA_vect){
  _softTCNT2 += 80;
  if(_softTCNT2 >= PWM_CYCLE_US) // A pwm cycle ends
  {
    _softTCNT2 = 0;
    // Set all pins to high level
    for(int i = 0; i < SERVO_NUM; ++i)
      digitalWrite(_servoMap[i], HIGH);
  }
  // Change PWM state if reachs the drop edge
  for(int i = 0; i < SERVO_NUM; ++i)
  {
    if(_softTCNT2 == _internalPWMLowPos[i])
      digitalWrite(_servoMap[i], LOW);
  }
 // Change duty cycle if needed
 if(_PWMChangeFlag == true)
  memcpy(_internalPWMLowPos, _desiredPWMLowPos, sizeof(_internalPWMLowPos));
}

bool updatePWM(const uint8_t &index, const uint16_t &lowPos)
{
  if(lowPos > PWM_CYCLE_US || (lowPos % 80 != 0))
    return false;
  _desiredPWMLowPos[index] = lowPos;
  _PWMChangeFlag = true;
  return true; 
}

void San_Diego(){
  
//    updatePWM(0, 1600);
//    delay(1000);
//    updatePWM(0, 800);
//    delay(1000);
  updatePWM(2,2160);  // 转向碗
  delay(1000);
  updatePWM(1,2320);  // 低头
  delay(1000);
  updatePWM(0, 1360); // 夹子闭合
  delay(1000);
  //updatePWM(1,2080);  //抬头
  updatePWM(1, 1600);
  delay(1000);
  updatePWM(2,1760);  // 转向花盆
  delay(1000);
  updatePWM(1, 2400); //低头
  delay(600);
  updatePWM(0,1600);  // 夹子打开
  delay(800);
  updatePWM(1,1600);  // 抬头
  delay(600);
  updatePWM(2,1040);  // 转向车头
  delay(600);
}
