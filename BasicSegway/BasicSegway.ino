double pitch;

int RMPin = 3;
int LMPin = 5;

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

  if (pitch > 0)
    analogWrite(LMPin, 250);
  } else {
    analogWrite(LMPin, 180);

  }
  
  //motorWrapper(LMPin, crunchPID(convertToPower(pitch)));
  //analogWrite(LM, 250);

}
