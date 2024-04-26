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
  float evaluate(float x, float y);

  //Subfunction
  vector<float> get_coefficient();
  void set_coefficients(const std::vector<float>& value);

  inline bool has_been_computed(){return (degree != 0);}

private:
  Eigen::VectorXf P;
  int degree = 0;
};

}
