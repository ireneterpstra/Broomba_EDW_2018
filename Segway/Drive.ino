/*Setup Motor pins*/
void setupMotors(int M1, int M2){
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
}

/*Converts power input (-100, 100) into PWM accepted by speed contolers (124, 253)*/
void motorWrapper(int motor, int motorPower){
  if (motorPower > 2){
    motorPower = motorPower + 3;
  } else if (motorPower < -2){
    motorPower = motorPower - 3; 
  }
  int power =  map(motorPower, -100, 100, 124, 253); //Divide motor power by range of expected input (in this case it is [-100, 100])
  //Serial.println(power);

  analogWrite(motor, power);
}
