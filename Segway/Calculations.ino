int convertToPower(double pitch){
  return map(pitch, -12, 12, -60, 60);
}

//void eStop(){
//  if (pitch > 12 || pitch < -12) { // || (pitch > -1 && pitch < 1)){ Dead Zone
//    eStopOn = true;
//  } else if (pitch > -1 && pitch < 1){
//    eStopOn = false;
//  } 
//}

void setTurnFactor(){
  if (X_val > 550){
    turnFactor = map(X_val, 550, 1023, 0 , 30);
  } else if (X_val < 480){
    turnFactor = map(X_val, 0, 480, -30 , 0);
  } else {
    turnFactor = 0;
  }
}

