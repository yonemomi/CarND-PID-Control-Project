#ifndef PID_H
#define PID_H
#include <uWS/uWS.h>

class PID {
 public:
  /**
   * Constructor
   */
  PID();

  /**
   * Destructor.
   */
  virtual ~PID();

  /**
   * Initialize PID.
   * @param (Kp_, Ki_, Kd_) The initial PID coefficients
   */
  void Init(double Kp_, double Ki_, double Kd_);

  /**
   * Update the PID error variables given cross track error.
   * @param cte The current cross track error
   */
  void UpdateError(double cte);

  /**
   * Calculate the total PID error.
   * @output The total PID error
   */
  double TotalError();

  bool Twiddle(double tol, double cte, uWS::WebSocket<uWS::SERVER> ws);
  void Reset(uWS::WebSocket<uWS::SERVER> ws);
  bool is_twiddled;

 private:
  /**
   * PID Errors
   */
  double p_error;
  double i_error;
  double d_error;

  /**
   * PID Coefficients
   */
  double Kp;
  double Ki;
  double Kd;
  /**
   * Twiddle
   */
  int checking_column;
  int checking_status;
  double best_err;
  double err;

  double Dp;
  double Di;
  double Dd;
};

#endif  // PID_H