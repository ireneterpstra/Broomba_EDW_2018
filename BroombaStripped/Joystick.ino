/*Arduino pin numbers*/
const int SW_pin = 4; // digital pin connected to switch output
const int X_pin = A1; // analog pin connected to X output
const int Y_pin = A0; // analog pin connected to Y output

int buttonState;

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

  buttonState = digitalRead(SW_pin);
  X_val = analogRead(X_pin); // Read potentiometer value
  Y_val = analogRead(Y_pin);
  
  setTurnFactor();
}

boolean buttonPressed(){
  if (buttonState == HIGH) {
    return false;
  } else {
    return true;
  }
}

boolean Y_down(){
  return Y_val < 100;
}

boolean Y_up(){
  return Y_val > 900;
}

boolean X_right(){
  return X_val > 900;
}

boolean X_left(){
  return X_val < 100;
}







