/* Motor power function*/



void setupMotors(int M1, int M2){
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
}

void motorWrapper(int motor, int motorPower){
  if (motorPower > 2){
    motorPower = motorPower + 3;
  } else if (motorPower < -2){
    motorPower = motorPower - 3; 
  }
  int power =  map(motorPower, -100, 100, 124, 253); //Divide motor power by range of expected input (in this case it is [-100, 100])
  Serial.println(power);
  analogWrite(motor, power);
}
