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
  // Point the arm to the bowl
  updatePWM(3, 1440);
  delay(600);
  // Put down the robotic arm
  updatePWM(2, 1280);
  delay(1000);
  // Close the clip
  updatePWM(0, 1920);
  delay(1000);
  // Raise the arm
  updatePWM(2, 720);
  delay(1000);
  // Point to the flower
  updatePWM(3, 1760);
  delay(1000);
  // Put down the arm
  updatePWM(1, 1280);
  updatePWM(2, 1520);
  delay(1000);
  // Release the clip
  updatePWM(0, 1280);
  delay(1000);
  // Repos the arm
  updatePWM(2, 720);
  updatePWM(1, 2240);
  delay(1000);
  updatePWM(3, 1200);
  delay(1000);

}
