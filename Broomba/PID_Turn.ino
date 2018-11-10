#define Pt 0.07//0.001 0.01
#define It 0.005//0.002 0.01
#define Dt 0.005//0.00025  0.0025
#define dtt 0.014

#define CONTt false
#define MAX_INt 65
#define MIN_INt -65
#define MAX_OUTt 90
#define MIN_OUTt -90

double prevErrorT = 0;
double currentErrorT = 0;
double totalErrorT = 0;

double setPointT;

double crunchPIDt(double input) {
  double pValue, iValue, dValue;

  currentErrorT = setPointT - input;
  if (CONTt) {
    if (abs(currentErrorT) > (MAX_INt - MIN_INt) / 2) {
      currentErrorT  = currentErrorT > 0 ? currentErrorT - MAX_INt + MIN_INt : currentErrorT + MAX_INt - MIN_INt;
    }
  }

  if (currentErrorT * Pt < MAX_OUTt && currentErrorT * Pt > MIN_OUTt) {

    totalErrorT += currentErrorT;
  } else {
    totalErrorT = 0;
  }

  //pValue = Math.abs(currentError) < acceptableRange ? 0: p * currentError;
  pValue = Pt * currentErrorT;
  iValue = It * totalErrorT * dtt;
  dValue = Dt * (currentErrorT - prevErrorT) / dtt;


  prevErrorT = currentErrorT;
  return constrain(pValue + iValue + dValue, MIN_OUTt, MAX_OUTt);
}


void setPIDSetpointT(double val) {
  setPointT = val;
}
