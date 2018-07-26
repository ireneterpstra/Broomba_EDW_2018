enum State {CALIBRATE, INERT, SELF_STANDING, RUN, STOP, ESTOP};
uint8_t state = INERT;

int X_val;
int Y_val;

double pitch;

int RMPin = 10;
int LMPin = 9;

double LM = 0;
double RM = 0;

double turnFactor;

void serialOutput(){
  Serial.print(pitch);
  //Serial.print(" + ");
  //Serial.print(convertToPower(pitch));
  //Serial.print(" + ");
  //Serial.println(crunchPID(convertToPower(pitch)));
  Serial.print(" : LM: " + String(LM));
  Serial.print(" : RM: " + String(RM));
  Serial.print(" Turn Factor  " + String(turnFactor));
  //Serial.print(" X_val  " + String(X_val));
  //Serial.print(" Y_val  " + String(Y_val));
  //Serial.print(" Button Pressed  " + String(buttonPressed()));
}

void setup() {
  Serial.begin(9600);

  setupMPU();
  setupMotors(RMPin, LMPin);
  setPIDSetpoint(0);
  setupJoystick();
  //Calibration Code
}

void loop() {
  loopMPU();
  loopJoystick();
  loopMPU();
  serialOutput();
  loopMPU();


  switch(state){
    case CALIBRATE: // set user's vertical, test motor power ratio/turn ratio -> inert
      Serial.println(" CALIBRATE");
      
      if(calToInert()){
        state = INERT;
      }
      break;
    case INERT: // no movement, initial state -> self_standing, calibrate
      Serial.println(" INERT");
      LM = 0;
      RM = 0;
      if(inertToCal()){
        state = CALIBRATE;
      } else if(inertToSS()){
        state = SELF_STANDING;
      }
      break;
    case SELF_STANDING: // riderless balancing, waits for rider -> run
      Serial.println(" SELF_STANDING");
      LM = crunchPIDs(convertToPower(pitch));
      RM = crunchPIDs(convertToPower(-pitch));
      
      if(ssToRun()){
        state = RUN;
      }
      break;
    case RUN: // normal operation -> stop, eStop
      Serial.println(" RUN");
      LM = crunchPID(convertToPower(pitch) - turnFactor);
      RM = crunchPID(convertToPower(-pitch) - turnFactor);
      
      if(runToStop()){
        state = STOP;
      } else if (runToEStop()){
        state = ESTOP;
      }
      break;
    case STOP: // get rider vertical, end condition -> run, inert
      Serial.println(" STOP");
      LM = crunchPIDst(convertToPower(pitch));
      RM = crunchPIDst(convertToPower(-pitch));
      
      if(stopToRun()){
        state = RUN;
      } else if (stopToInert()){
        state = INERT;
      }
      break;
    case ESTOP: // get rider vertical in case of emergency, accompanied by warning -> stop
      Serial.println(" ESTOP");
      LM = crunchPIDst(convertToPower(pitch));
      RM = crunchPIDst(convertToPower(-pitch));

      // add warning noise
      
      if(eStopToStop()){
        state = STOP;
      }
      break;
  }





  
//  switch(state){
//    case INITIALIZE: // (Pause State / Inert Pause)
//      LM = 0;
//      RM = 0;
//      //Check Battery Power for 9/12V batteries
//      //System Check
//      //PowerUp self test
//      //make complicated start function / press button / wiggle joystick 3 times
//      if(buttonPressed){
//        state = E_STOP;
//      }
//      break;
//
//    // Add case for just balancing / mounting the segway? (gain is different than for when someone is on it) Pause?
//    
//    case RUN: //  (Normal / Emergency Stop -> vertical w person)
//      LM = crunchPID(convertToPower(pitch) - turnFactor);
//      RM = crunchPID(convertToPower(-pitch) - turnFactor); // change turn factor for going backwards
//      if(pitch > 12 || pitch < -12){ // Approaching critical speed forces a vertical realignment (get max speed from current)
//        state = E_STOP;
//      } else if (buttonPressed){ // Accidental press? diffrent sensor / X forward + hit button (need dead zone)
//        state = E_STOP; 
//      }
//      break;
//    case E_STOP: // -> dont stop, get rider vertical
//      LM = 0;
//      RM = 0;
//      if(pitch > -1 && pitch < 1){
//        state = RUN;
//      }
//      break;
      
    //Add resistor to handels and measure wether you are not holding it

    //Right Segway -> vertical realignment
    //Get off mode? Pause?
    //Power down state?

    //Need user feedback to indicate state / how critical your position/speed is

    //Calibrate -> need to fix what vertical means
    //Inert
    //Self-Standing
    //Run
    //Stop
    //EmergencyStop

//  }
  
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
