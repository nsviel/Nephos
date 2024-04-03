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
  void compute(const std::vector<glm::vec3>& xyz, int degree, vec2 x_bound, vec2 y_bound);
  double evaluate(double x, double y);

  //Subfunction
  vector<double> get_coefficient();
  void set_coefficients(const std::vector<double>& value);
  
  inline bool has_been_computed(){return (degree != 0);}

private:
  Eigen::VectorXd coef;
  int degree = 0;
};

}
