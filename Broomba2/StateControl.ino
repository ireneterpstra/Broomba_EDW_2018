// INERT transitions ---------------------------------------------
boolean inertToCal(){
  return buttonPressed() && X_left();
}

boolean inertToSS(){
  return buttonPressed() && X_right();
}

// CALIBRATE transitions -----------------------------------------
boolean calToInert(){
  return buttonPressed() && Y_up();
}

// SELF_STANDING transitions -------------------------------------
boolean ssToRun(){
  return buttonPressed() && Y_up();
}

// RUN transitions -----------------------------------------------
boolean runToStop(){
  return buttonPressed() && Y_down();
}

boolean runToEStop(){
  return pitch > 20 || pitch < -20;
}

// STOP transitions -----------------------------------------------
boolean stopToRun(){
  return buttonPressed() && X_right();
}

boolean stopToInert(){
  return buttonPressed() && X_left();
}

// ESTOP transitions ----------------------------------------------
boolean eStopToStop(){
  return buttonPressed() && Y_up();
}

// Test transitions -----------------------------------------------
boolean goToTestState(){
  return buttonPressed() && Y_up();
}
boolean backToInert(){
  return buttonPressed() && Y_down();
}
