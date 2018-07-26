#define Ps 2.5//0.001 0.01
#define Is 0.0//0.002 0.01
#define Ds 0.005//0.00025  0.0025
#define dts 0.014

#define CONTs false
#define MAX_INs 65
#define MIN_INs -65
#define MAX_OUTs 90
#define MIN_OUTs -90

double prevErrorS = 0;
double currentErrorS = 0;
double totalErrorS = 0;

double setPointS;

double crunchPIDs(double input) {
  double pValue, iValue, dValue;

  currentErrorS = setPointS - input;
  if (CONTs) {
    if (abs(currentErrorS) > (MAX_INs - MIN_INs) / 2) {
      currentErrorS  = currentErrorS > 0 ? currentErrorS - MAX_INs + MIN_INs : currentErrorS + MAX_INs - MIN_INs;
    }
  }

  if (currentErrorS * Ps < MAX_OUTs && currentErrorS * Ps > MIN_OUTs) {

    totalErrorS += currentErrorS;
  } else {
    totalErrorS = 0;
  }

  //pValue = Math.abs(currentError) < acceptableRange ? 0: p * currentError;
  pValue = Ps * currentErrorS;
  iValue = Is * totalErrorS * dts;
  dValue = Ds * (currentErrorS - prevErrorS) / dts;


  prevErrorS = currentErrorS;
  return constrain(pValue + iValue + dValue, MIN_OUTs, MAX_OUTs);
}


void setPIDSetpointS(double val) {
  setPointS = val;
}


