#define Pst 1.5//0.001 0.01
#define Ist 0.0//0.002 0.01
#define Dst 0.005//0.00025  0.0025
#define dtst 0.014

#define CONTst false
#define MAX_INst 65
#define MIN_INst -65
#define MAX_OUTst 90
#define MIN_OUTst -90

double prevErrorSt = 0;
double currentErrorSt = 0;
double totalErrorSt = 0;

double setPointSt;

double crunchPIDst(double input) {
  double pValue, iValue, dValue;

  currentErrorSt = setPointSt - input;
  if (CONTst) {
    if (abs(currentErrorSt) > (MAX_INst - MIN_INst) / 2) {
      currentErrorSt  = currentErrorSt > 0 ? currentErrorSt - MAX_INst + MIN_INst : currentErrorSt + MAX_INst - MIN_INst;
    }
  }

  if (currentErrorSt * Pst < MAX_OUTst && currentErrorSt * Pst > MIN_OUTst) {

    totalErrorSt += currentErrorSt;
  } else {
    totalErrorSt = 0;
  }

  //pValue = Math.abs(currentError) < acceptableRange ? 0: p * currentError;
  pValue = Pst * currentErrorSt;
  iValue = Ist * totalErrorSt * dtst;
  dValue = Dst * (currentErrorSt - prevErrorSt) / dtst;


  prevErrorSt = currentErrorSt;
  return constrain(pValue + iValue + dValue, MIN_OUTst, MAX_OUTst);
}


void setPIDSetpointSt(double val) {
  setPointSt = val;
}


