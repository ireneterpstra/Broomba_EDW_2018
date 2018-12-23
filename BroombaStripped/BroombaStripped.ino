#include <Math.h>
/*
   * Irene Terpstra
   * 12/27/2018 
   EDW 2018 - Broomba
   Tester for possible memory leak
   */

/*States*/
enum State {INERT, RUN};
/*Starting State*/
uint8_t state = RUN;

/*Joystick values*/
int X_val;
int Y_val;

/*Pitch from IMU*/
double pitch;
double previousPitch;

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

double centerIMU = -3;


/*All serial output (keeps everything neat)*/
void serialOutput() {
  Serial.print(pitch - centerIMU);
  Serial.print(" + ");
  Serial.print("Total Error: " + String(getTotError()));
  Serial.print(" + ");
  Serial.print("Power: " + String(power));
  Serial.print(" + ");
  //  Serial.print(convertToPower(pitch));
  //Serial.print(" + ");
  //Serial.println(crunchPID(convertToPower(pitch)));
  //  Serial.print(" : LM: " + String(LM));
  //  Serial.print(" : RM: " + String(RM));
  //  Serial.print(" Turn Factor  " + String(turnFactor));
  //  Serial.print(" X_val  " + String(X_val));
  //  Serial.print(" Y_val  " + String(Y_val));
  //  Serial.print(" Button Pressed  " + String(buttonPressed()));
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
  setupJoystick();
  //Calibration Code


  //setup interrupts
//  TIMSK2 = (TIMSK2 & B11111110) | 0x01; //turns on interrupt on timer 2
//  TCCR2B = (TCCR2B & B11111000) | 0x06; //prescalar of 128
//  TIMSK0 = (TIMSK2 & B11111110) | 0x01; //turns on interrupt on timer 2
//  TCCR0B = (TCCR2B & B11111000) | 0x05; //prescalar of 128
}

void loop() {
  //Serial.println("WHATSUP DUDE");
  loopMPU();
  loopJoystick();
  serialOutput();


  int tempePitch = -pitch + centerIMU;
  if (tempePitch > 0) {
    power = crunchPID(pow(tempePitch, 0.6));
  } else {
    power = crunchPID(-pow(-tempePitch, 0.6));
  }



  /*State Machine controls what state the segway is in*/
  switch (state) {

    /*INERT: no movement, initial state -> self_standing, calibrate --------------------------*/
    case INERT:
      Serial.println(" INERT");
      LM = 0;
      RM = 0;
      //      if(inertToCal()){
      //        state = CALIBRATE;
      //      } else
      if (goToTestState()) {
        state = RUN;
      }
      break;

    /*RUN: normal operation -> stop, eStop ---------------------------------------------------*/
    case RUN:
      Serial.println(" RUN");

      LM = power; //- turnFactor;
      RM = power; //+ turnFactor;

      if (backToInert()) {
        state = INERT;
      } else if (runToEStop()) {
        state = INERT;
      }
      break;
  }

  /*Input final calculated power to motors*/
  motorWrapper(LMPin1, LM);
  motorWrapper(LMPin2, LM);
  motorWrapper(RMPin1, RM);
  motorWrapper(RMPin2, RM);
}


