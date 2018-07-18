double pitch=0;

void setup(){ 
  Serial.begin(9600);
  setupGyro();
  setPIDSetpoint(0);
  
}

void loop(){
  loopGyro();
  int power= convertAngleToPower(pitch);
  setMotors(power, power);
  Serial.println(pitch);
}


