#pragma once

#include <Utility/Specific/Common.h>


namespace ope::fitting{

class Polyfit
{
public:
  Polyfit();
  ~Polyfit();

public:
  //Main function
  void compute(const std::vector<float>& x, const std::vector<float>& y, const std::vector<float>& z, int degree);
  double evaluate(double x, double y);

private:
  Eigen::VectorXd coef;
  ine degree = 0;
};

}
