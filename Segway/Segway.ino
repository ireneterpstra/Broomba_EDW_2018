double pitch;

boolean eStopOn = false;

int RMPin = 10;
int LMPin = 9;

double MP;

void setup() {
  Serial.begin(9600);

  setupMPU();
  setupMotors(RMPin, LMPin);
  setPIDSetpoint(0);
}

void loop() {
  loopMPU();
  eStop();
  loopMPU();
  MP = crunchPID(convertToPower(pitch));
  loopMPU();
  Serial.print(pitch);
  //Serial.print(" + ");
  //Serial.print(convertToPower(pitch));
  //Serial.print(" + ");
  //Serial.println(crunchPID(convertToPower(pitch)));
  Serial.print(F(" : Emergency Stop on: "));
  Serial.print(eStopOn);
  Serial.print(F(" : MP: "));
  Serial.println(MP);
  //Serial.println(" : RM: " + String(-MP));
  loopMPU();


  motorWrapper(LMPin, RMPin, MP);
  //motorWrapper(RMPin, -MP);
  //analogWrite(LM, 250);

}
