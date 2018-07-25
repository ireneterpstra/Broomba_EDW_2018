double pitch;

boolean eStopOn;

int RMPin = 10;
int LMPin = 9;

double LM;
double RM;

double turnFactor;

void setup() {
  Serial.begin(9600);

  setupMPU();
  setupMotors(RMPin, LMPin);
  setPIDSetpoint(0);
  setupJoystick();
  eStopOn = true;
}

void loop() {
  loopJoystick();
  loopMPU();
  eStop();
  loopMPU();
  LM = crunchPID(convertToPower(pitch) - turnFactor);
  loopMPU();
  RM = crunchPID(convertToPower(-pitch) - turnFactor);
  loopMPU();
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
  loopMPU();


  motorWrapper(LMPin, LM);
  motorWrapper(RMPin, RM);
  //analogWrite(LM, 250);

}
