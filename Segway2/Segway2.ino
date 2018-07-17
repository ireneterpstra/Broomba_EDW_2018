double pitch=0;

void setup(){ 
  setupGyro();
}

void loop(){
  loopGyro();
  int power= convertAngleToPower(pitch);
  setMotors(power, power);
}


