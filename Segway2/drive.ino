#define leftPin 3
#define rightPin 5



void setupMotors(){
  pinMode(leftPin, OUTPUT);
  pinMode(rightPin, OUTPUT);
}

void setMotors(double leftVoltage, double rightVoltage) {
int rightPWM =  map(rightVoltage, -101, 101, 124, 254); //Divide motor power by range of expected input (in this case it is [-100, 100])
int leftPWM =  map(leftVoltage, -101, 101, 124, 254); //Divide motor power by range of expected input (in this case it is [-100, 100])

  //Serial.println(leftVoltage);
  //Serial.println(leftPWM);
  
  analogWrite(leftPin, leftPWM);
  analogWrite(rightPin, leftPWM);

}

