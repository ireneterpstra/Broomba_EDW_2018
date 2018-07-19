double pitch;

int RMPin = 10;
int LMPin = 9;

int RM;
int LM;

void setup() {
  Serial.begin(9600);

  setupMPU();
  setupMotors(RMPin, LMPin);
  setPIDSetpoint(0);
}

void loop() {
  loopMPU();
  Serial.println  (pitch);
  //Serial.print(" + ");
  //Serial.print(convertToPower(pitch));
  //Serial.print(" + ");
  //Serial.println(crunchPID(convertToPower(pitch)));

  motorWrapper(LMPin, crunchPID(convertToPower(-pitch)));
  motorWrapper(RMPin, crunchPID(convertToPower(pitch)));
  //analogWrite(LM, 250);

}
