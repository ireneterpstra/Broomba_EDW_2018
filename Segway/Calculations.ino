int convertToPower(double pitch){
  int power = 0;
  if (pitch > 20|| pitch < -20 || (pitch > -2 && pitch < 2)){
    power = 0;
  } else {
    power = map(pitch, -45, 45, -70, 70);
  }
  return power;
}
