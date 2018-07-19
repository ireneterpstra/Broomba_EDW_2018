int convertToPower(double pitch){
  int power = 0;
  if (pitch > 20|| pitch < -20) { // || (pitch > -1 && pitch < 1)){ Dead Zone
    power = 0;
  } else {
    power = map(pitch, -20, 20, -70, 70);
  }
  return power;
}
