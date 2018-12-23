#define P 7.2//0.001 0.01 1.0
#define I 38.4//0.002 0.01 1.0
#define D 0.000//0.00025  0.0025 0.005
#define dt 0.014

#define CONT false
#define MAX_IN 65
#define MIN_IN -65
#define MAX_OUT 50
#define MIN_OUT -50

#define MAXiError (MAX_OUT/I/dt)

double prevError = 0;
double currentError = 0;
double totalError = 0;

double setPoint;

double crunchPID(double input) {
  double pValue, iValue, dValue;

  currentError = setPoint - input;
  if (CONT) {
    if (abs(currentError) > (MAX_IN - MIN_IN) / 2) {
      currentError  = currentError > 0 ? currentError - MAX_IN + MIN_IN : currentError + MAX_IN - MIN_IN;
    }
  }

  if (currentError * P < MAX_OUT && currentError * P > MIN_OUT) {
    totalError += currentError;
  } else {
    totalError = 0;
  }
  totalError = constrain(totalError, -MAXiError, MAXiError);

  //pValue = Math.abs(currentError) < acceptableRange ? 0: p * currentError;
  pValue = P * currentError;
  iValue = I * totalError * dt;
  dValue = D * (currentError - prevError) / dt;


  prevError = currentError;
  return constrain(pValue + iValue + dValue, MIN_OUT, MAX_OUT);
}


void setPIDSetpoint(double val) {
  setPoint = val;
}

double getTotError(){
  return totalError;
}


