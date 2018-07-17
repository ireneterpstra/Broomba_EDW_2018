double pitch;

int RMPin = A0;
int LMPin = A1;

int RM;
int LM;

void setup() {
  Serial.begin(9600);

  setupMPU();
  
}

void loop() {
  loopMPU();
  //Serial.print(pitch);
  //Serial.print(" + ");
  //Serial.println(convertToPower(pitch));
  motorWrapper(RM, pitch);
}
