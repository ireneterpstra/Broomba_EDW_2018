/*
 * Irene Terpstra
 * 8/1/2018 
 * EDW 2018 - Broomba
 * Segway with multiple states
 */

/*States*/
enum State {CALIBRATE, INERT, SELF_STANDING, RUN, STOP, ESTOP};
/*Starting State*/
uint8_t state = RUN;

/*Joystick values*/
int X_val;
int Y_val;

/*Pitch from IMU*/
double pitch;

/*Motor Pins*/
int RMPin1 = 11;
int RMPin2 = 10;
int LMPin1 = 9;
int LMPin2 = 3;
/*Secondary switch pin*/
//int sPin = 13;

/*Motor Powers (set in each state)*/
double LM = 0;
double RM = 0;
double power;
/*Turning factor*/
double turnFactor;
double turn;


/*All serial output (keeps everything neat)*/
void serialOutput(){
  Serial.print(pitch);
  Serial.print(" + ");
  Serial.print(String(turn));
  Serial.print(" + ");
  //Serial.print(convertToPower(pitch));
  //Serial.print(" + ");
  //Serial.println(crunchPID(convertToPower(pitch)));
  Serial.print(" : LM: " + String(LM));
  Serial.print(" : RM: " + String(RM));
  //Serial.print(" Turn Factor  " + String(turnFactor));
  Serial.print(" X_val  " + String(X_val));
  Serial.print(" Y_val  " + String(Y_val));
  Serial.print(" Button Pressed  " + String(buttonPressed()));
  //Serial.print("Switched: " + String(switched()));
}

/*Checks for secondary switch state*/
//boolean switched(){
//  int buttonState = digitalRead(sPin);
//  if (buttonState == HIGH) {
//    return false;
//  } else {
//    return true;
//  }
//}

void setup() {
  Serial.begin(9600);

  setupMPU();
  setupMotors(RMPin1, RMPin2, LMPin1, LMPin2);
  setPIDSetpoint(0);
  setPIDSetpointS(0);
  setPIDSetpointSt(0);
  setPIDSetpointT(0);
  setupJoystick();
  //Calibration Code

//  pinMode(sPin, INPUT_PULLUP);
}

void loop() {
  loopMPU();
  loopJoystick();
  loopMPU();
  serialOutput();
  loopMPU();


/*State Machine controls what state the segway is in*/
  switch(state){

/*CALIBRATE: set user's vertical, test motor power ratio/turn ratio -> inert ------------*/
    case CALIBRATE: 
      Serial.println(" CALIBRATE");
      
      if(calToInert()){
        state = INERT;
      }
      break;

/*INERT: no movement, initial state -> self_standing, calibrate --------------------------*/
    case INERT: 
      Serial.println(" INERT");
      LM = 0;
      RM = 0;
      if(inertToCal()){
        state = CALIBRATE;
      } else if(goToTestState()){
        state = RUN;
      }
      break;

/*SELF_STANDING: riderless balancing, waits for rider -> run -----------------------------*/
    case SELF_STANDING: 
      Serial.println(" SELF_STANDING");
      LM = crunchPIDs(convertToPower(pitch+14.9));
      RM = crunchPIDs(convertToPower(-pitch-14.9));  // use inv tan instead of prop control for better results
      
      if(backToInert()){
        state = INERT;
      }
      break;

/*RUN: normal operation -> stop, eStop ---------------------------------------------------*/
    case RUN: 
      Serial.println(" RUN");
      power = crunchPID(convertToPower(pitch));
      LM = power + turnFactor;
      RM = power - turnFactor;
      
      if(backToInert()){
        state = INERT;
      } else if (runToEStop()){
        state = INERT;
      }
      break;

/*STOP: get rider vertical, end condition -> run, inert-----------------------------------*/
    case STOP: 
      Serial.println(" STOP");
      LM = crunchPIDst(convertToPower(pitch));
      RM = crunchPIDst(convertToPower(-pitch));
      
      if(stopToRun()){
        state = RUN;
      } else if (stopToInert()){
        state = INERT;
      }
      break;

/*ESTOP: get rider vertical in case of emergency, accompanied by warning -> stop ---------*/
    case ESTOP: 
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


/*Input final calculated power to motors*/
  motorWrapper(LMPin1, LM);
  motorWrapper(LMPin2, LM);
  motorWrapper(RMPin1, RM);
  motorWrapper(RMPin2, RM);
}
