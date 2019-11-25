/*Turns pitch of segway (-12, 12) to a desired speed (-60, 60)*/
int convertToPower(double pitch) {
  return map(pitch, -30, 30, -60, 60);
}

//void eStop(){
//  if (pitch > 12 || pitch < -12) { // || (pitch > -1 && pitch < 1)){ Dead Zone
//    eStopOn = true;
//  } else if (pitch > -1 && pitch < 1){
//    eStopOn = false;
//  }
//}

/*Converts joystick X_Value (0, 1023) to (-30, 30) turn value*/
void setTurnFactor(){
  if (Y_val > 550){
    turnFactor = map(Y_val, 550, 1023, 0 , 20);
  } else if (Y_val < 480){
    turnFactor = map(Y_val, 0, 480, -20 , 0);
  } else {
    turnFactor = 0;
  }
}

