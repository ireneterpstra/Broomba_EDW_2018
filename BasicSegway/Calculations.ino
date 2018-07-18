int convertToPower(double pitch){
  int power = 0;
  if (pitch > 45 || pitch < -45){
    power = 0;
  } else {
    power = map(pitch, -45, 45, -100, 100);
  }
  return power;
}
