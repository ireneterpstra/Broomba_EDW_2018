/* Motor power function*/
void motorWrapper(int motor, int motorPower){
  int power = motorPower;
  power =  map(motorPower, -101, 101, 124, 254); //Divide motor power by range of expected input (in this case it is [-100, 100])
  Serial.println(power);
  analogWrite(motor, power);
  analogWrite(motor, power);
}

int convertToPower(double pitch){
  int output = 0;
  if (pitch >= 0){
    output = map(pitch, 0, 45, 0, 100);
  } else {
    output = map(pitch, -45, 0, -100, 0);
  }
  return output;
}
