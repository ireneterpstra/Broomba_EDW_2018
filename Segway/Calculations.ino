int convertToPower(double pitch){
  int power = 0;
  if (pitch > 8|| pitch < -8) { // || (pitch > -1 && pitch < 1)){ Dead Zone
    power = 0;
  } else {
    power = map(pitch, -8, 8, -30, 30);
  }
  return power;
}
