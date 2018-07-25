enum State {STARTUP, RUN, E_STOP};
uint8_t state = STOP;

double pitch;

boolean eStopOn;

int RMPin = 10;
int LMPin = 9;

double LM;
double RM;

double turnFactor;

void serialOutput(){
  Serial.print(pitch);
  //Serial.print(" + ");
  //Serial.print(convertToPower(pitch));
  //Serial.print(" + ");
  //Serial.println(crunchPID(convertToPower(pitch)));
  Serial.print(F(" : Emergency Stop on: "));
  Serial.print(eStopOn);
  Serial.print(F(" : LM: "));
  Serial.print(LM);
  Serial.print(" : RM: " + String(RM));
  Serial.println(" Turn Factor  " + String(turnFactor));
}

void setup() {
  Serial.begin(9600);

  setupMPU();
  setupMotors(RMPin, LMPin);
  setPIDSetpoint(0);
  setupJoystick();
  eStopOn = true;
}

void loop() {
  loopMPU();
  loopJoystick();
  serialOutput();
  
  switch(state){
    case STARTUP:
      LM = 0;
      RM = 0;
      if(pitch > -1 && pitch < 1){
        state = RUN;
      }
      break;
    case RUN:
      LM = crunchPID(convertToPower(pitch) - turnFactor);
      RM = crunchPID(convertToPower(-pitch) - turnFactor);
      if(pitch > 12 || pitch < -12){
        state = E_STOP;
      }
      break;
    case E_STOP:
      LM = 0;
      RM = 0;
      if(pitch > -1 && pitch < 1){
        state = RUN;
      }
      break;
  }
  
//  loopMPU();
//  //eStop();
//  loopMPU();
//  LM = crunchPID(convertToPower(pitch) - turnFactor);
//  loopMPU();
//  RM = crunchPID(convertToPower(-pitch) - turnFactor);
//  loopMPU();
//  loopMPU();


  motorWrapper(LMPin, LM);
  motorWrapper(RMPin, RM);
}
