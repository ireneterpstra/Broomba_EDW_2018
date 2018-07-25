// Arduino pin numbers
const int SW_pin = 4; // digital pin connected to switch output
const int X_pin = A1; // analog pin connected to X output
const int Y_pin = A0; // analog pin connected to Y output

void setupJoystick() {
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  // initialize the pushbutton pin as an input:
  //pinMode(4, INPUT);
}

void loopJoystick() {
//  Serial.print("Switch:  ");
//  Serial.print(digitalRead(SW_pin));
//  Serial.print("\n");
//  Serial.print("X-axis: ");
//  Serial.print(analogRead(X_pin));
//  Serial.print("\n");
//  Serial.print("Y-axis: ");
//  Serial.println(analogRead(Y_pin));
//  Serial.print("\n\n");

  int buttonState = digitalRead(SW_pin);
  if (buttonState == HIGH) {
    buttonPressed = true;
  } else {
    buttonPressed = false;
  }

  int potXValue = analogRead(X_pin); // Read potentiometer value
  int potYValue = analogRead(A1);
  
  turnFactor = map(potXValue, 0, 1023, -10 , 10); // Map the potentiometer value from jydrt
  if (turnFactor >= -1 && turnFactor < 1){
    turnFactor = 0;
  }
}
