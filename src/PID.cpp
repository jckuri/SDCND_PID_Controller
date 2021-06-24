#include "PID.h"

/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

#define VERY_NEGATIVE -1.0e10

void PID::Init(double Kp_, double Ki_, double Kd_) {
  /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   */
	Kp = Kp_;
	Ki = Ki_;
	Kd = Kd_;
  
	p_error = 0.0;
	i_error = 0.0;
	d_error = 0.0;
  
	previous_cte = VERY_NEGATIVE;
}

void PID::UpdateError(double cte) {
  /**
   * TODO: Update PID errors based on cte.
   */
  	if(previous_cte == VERY_NEGATIVE) previous_cte = cte;
	p_error = cte;
	i_error += cte;
	d_error = cte - previous_cte;
	previous_cte = cte;
	//printf("p_error=%f, i_error=%f, d_error=%f, previous_cte=%f\n", p_error, i_error, d_error, previous_cte);
}

double PID::TotalError() {
  /**
   * TODO: Calculate and return the total error
   */
	return -Kp * p_error - Ki * i_error - Kd * d_error;  // TODO: Add your total error calc here!
}