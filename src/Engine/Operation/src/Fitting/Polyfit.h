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
  void compute(const std::vector<glm::vec3>& points, int degree);
  double evaluate(double x, double y);

private:
  Eigen::VectorXd coef;
  int degree = 0;
};

}
