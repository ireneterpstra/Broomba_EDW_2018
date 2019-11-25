/*
   * Irene Terpstra
   * 8/1/2018 
   EDW 2018 - Broomba
   Segway with multiple states
   */

/*States*/
enum State {RUN, STOP};
/*Starting State*/
uint8_t state = STOP;

/*Pitch from IMU*/
double yaw;
double pitch;
double roll;

/*Joystick values*/
int X_val;
int Y_val;

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
void serialOutput() {
//  Serial.print("Pitch: " + String(pitch));
//  Serial.print(" + ");
//  Serial.print("Power: " + String(power));
//  Serial.print(" + ");
  Serial.print(" X_val  " + String(X_val));
  Serial.print(" Y_val  " + String(Y_val));
  //  Serial.print(convertToPower(pitch));
  //  Serial.print(" + ");
  //  //Serial.println(crunchPID(convertToPower(pitch)));
  //  Serial.print(" : LM: " + String(LM));
  //  Serial.print(" : RM: " + String(RM));
}

void setup() {
  Serial.begin(9600);

  setupBNO();
  setupMotors(RMPin1, RMPin2, LMPin1, LMPin2);
  setPIDSetpoint(0);
  setupJoystick();
}

void loop() {
  loopBNO();
  serialOutput();
  loopJoystick();

  /*State Machine controls what state the segway is in*/
  switch (state) {

    /*RUN: normal operation -> stop ---------------------------------------------------*/
    case RUN:
      Serial.println(" RUN");
      power = crunchPID(convertToPower(-pitch));
      //turn = crunchPIDt(turnFactor);
      LM = power;
      RM = power;

      if (pitch < -30 || pitch > 30) {
        state = STOP;
      }
      break;

    /*STOP: stop all motors -> run ----------------------------------------------------*/
    case STOP:
      Serial.println(" STOP");
      LM = 0;
      RM = 0;

      if (pitch > -5 && pitch < 5) {
        state = RUN;
      }
      break;
  }

  /*Input final calculated power to motors*/
  motorWrapper(LMPin1, LM);
  motorWrapper(LMPin2, LM);
  motorWrapper(RMPin1, RM);
  motorWrapper(RMPin2, RM);
  delay(100);
}
