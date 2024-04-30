#pragma once

#include <Eigen/Dense>
#include <glm/glm.hpp>
#include <vector>


namespace ope::fitting{

class Polyfit
{
public:
  Polyfit();
  ~Polyfit();

public:
  //Main function
  void compute(const std::vector<glm::vec3>& points, int degree);
  void compute(const std::vector<glm::vec3>& xyz, int degree, glm::vec2 x_bound, glm::vec2 y_bound);
  float evaluate(float x, float y);

  //Subfunction
  std::vector<float> get_coefficient();
  void set_coefficients(const std::vector<float>& value);

  inline bool has_been_computed(){return (degree != 0);}

private:
  Eigen::VectorXf P;
  int degree = 0;
};

}
