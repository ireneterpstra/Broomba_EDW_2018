 // Arduino pin numbers
const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output

void setupJoystick() {
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(115200);
}

void loopJoystick() {
  Serial.print("Switch:  ");
  Serial.print(digitalRead(SW_pin));
  Serial.print("\n");
  Serial.print("X-axis: ");
  Serial.print(analogRead(X_pin));
  Serial.print("\n");
  Serial.print("Y-axis: ");
  Serial.println(analogRead(Y_pin));
  Serial.print("\n\n");
  
 int potXValue = analogRead(A1); // Read potentiometer value
  //int potYValue = analogRead(A1);
 int pwmXOutput = map(potXValue, 0, 1023, -129, 129); // Map the potentiometer value from jydrt
}
  
 //analogWrite(5, pwmXOutput); // Send PWM signal to L298N Enable pin
 //analogWrite(6, 100 - pwmXOutput); // Send PWM signal to L298N Enable pin

 
 
// int power =  map(pwmXOutput, 0, 100, 124, 253); //Divide motor power by range of expected input (in this case it is [-100, 100])
  //Serial.println(power);
//  analogWrite(9, power);
//  analogWrite(10, power);
//256 221
