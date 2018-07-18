/* Motor power function*/



void setupMotors(int M1, int M2){
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
}

void motorWrapper(int motor, int motorPower){
  int power =  map(motorPower, -101, 101, 124, 254); //Divide motor power by range of expected input (in this case it is [-100, 100])
  Serial.println(power);
  analogWrite(motor, power);
}
