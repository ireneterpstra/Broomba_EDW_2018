int convertToPower(double pitch){
  int power = 0;
  if (eStopOn){
    power = 0;
  } else {
    power = map(pitch, -12, 12, -60, 60);
  }
  return power;
}

void eStop(){
  if (pitch > 12 || pitch < -12) { // || (pitch > -1 && pitch < 1)){ Dead Zone
    eStopOn = true;
  } else if (pitch > -1 && pitch < 1){
    eStopOn = false;
  } 
}

