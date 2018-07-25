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
  //Serial.println(power);
<<<<<<< HEAD
  analogWrite(motor1, power-129);
  analogWrite(motor2, -power-129);
=======
  analogWrite(motor, power);
  //analogWrite(motor2, -power);
>>>>>>> 67d210258eeb95edf393a43fc7bb2aec12a71b71
}
