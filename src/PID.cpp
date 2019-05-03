#include "PID.h"
#include <uWS/uWS.h>
#include <iostream>
#include <numeric>
#include <vector>

using std::vector;
/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
  /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   */
  Kp = Kp_;
  Ki = Ki_;
  Kd = Kd_;
  p_error = 1;
  i_error = 1;
  d_error = 1;
  is_twiddled = false;
  checking_column = 0;
  checking_status = 0;
  best_err = 100000.0;
  err = 0;
  Dp = 1;
  Di = 1;
  Dd = 1;
}

void PID::UpdateError(double cte) {
  /**
   * TODO: Update PID errors based on cte.
   */
  double prev_cte = p_error;
  p_error = cte;
  d_error = cte - prev_cte;
  i_error += cte;
}

double PID::TotalError() {
  /**
   * TODO: Calculate and return the total error
   */
  return -Kp * p_error - Ki * i_error -
         Kd * d_error;  // TODO: Add your total error calc here!
}

bool PID::Twiddle(double tol, double cte) {
  double sum = d_error + i_error + p_error;
  std::cout << "Twiddling" << std::endl;
  std::cout << "sum:" << sum << std::endl;

  while (sum > tol) {
    std::cout << "Intermediate result cte:" << cte << std::endl;

    std::cout << "Intermediate result sum:" << sum << std::endl;
    std::cout << "Intermediate result K:" << Kp << "," << Ki << "," << Kd
              << std::endl;
    std::cout << "Intermediate result D:" << p_error << "," << i_error << ","
              << d_error << std::endl;
    std::cout << "checking status:" << checking_status << std::endl;
    if (checking_status == 0) {
      best_err = cte;
      checking_status += 1;
    }
    if (checking_status == 1) {
      std::cout << "processing status 1" << std::endl;
      if (checking_column == 0) Kp += p_error;
      if (checking_column == 1) Ki += i_error;
      if (checking_column == 2) Kd += d_error;
      checking_status += 1;
    }
    if (checking_status == 2) {
      std::cout << "processing status 2" << std::endl;

      if (cte < best_err) {
        best_err = cte;
        if (checking_column == 0) p_error *= 1.1;
        if (checking_column == 1) i_error *= 1.1;
        if (checking_column == 2) d_error *= 1.1;
      } else {
        if (checking_column == 0) Kp -= 2 * p_error;
        if (checking_column == 1) Ki -= 2 * i_error;
        if (checking_column == 2) Kd -= 2 * d_error;
        checking_status += 1;

        if (checking_status == 3) {
          std::cout << "processing status 3" << std::endl;
          if (cte < best_err) {
            best_err = cte;
            if (checking_column == 0) p_error *= 1.1;
            if (checking_column == 1) i_error *= 1.1;
            if (checking_column == 2)
              d_error *= 1.1;
            else {
              if (checking_column == 0) Kp += p_error;
              if (checking_column == 1) Ki += i_error;
              if (checking_column == 2) Kd += d_error;
              if (checking_column == 0) p_error *= 0.9;
              if (checking_column == 1) i_error *= 0.9;
              if (checking_column == 2) d_error *= 0.9;
            }
          }
        }
      }
    }
    std::cout << "END OF LOOP" << std::endl;

    checking_status = 1;
    checking_column = (checking_column + 1) % 3;
  }
  std::cout << "BEST PARAMETER" << std::endl;
  std::cout << Kp << "," << Ki << "," << Kd << std::endl;

  is_twiddled = true;
  return true;
}
/*
 * make.robot() run
 * https://knowledge.udacity.com/questions/6171
 */
//void PID::Reset(uWS::WebSocket<uWS::SERVER> ws) {
  // restart the simulator
//  std::string reset_msg = "42[\"reset\",{}]";
//  ws.send(reset_msg.data(), reset_msg.length(), uWS::OpCode::TEXT);
//}
