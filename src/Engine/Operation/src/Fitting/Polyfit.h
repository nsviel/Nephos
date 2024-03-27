#pragma once

#include <Utility/Specific/common.h>


namespace ope::fitting{

class Polyfit
{
public:
  Polyfit();
  ~Polyfit();

public:
  //Main function
  Eigen::VectorXd compute(const Eigen::MatrixXd& data, int degree);
  double evaluate(const Eigen::VectorXd& params, double x, double y, int degree);
  
private:

};

}
