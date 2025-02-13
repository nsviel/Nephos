#pragma once

#include <Eigen/Dense>
#include <glm/glm.hpp>
#include <vector>


namespace ope::fitting{

class Surface
{
public:
  Surface();
  ~Surface();

public:
  //Main function
  void compute(std::vector<glm::vec3>& data);
  void compute(std::vector<glm::vec3>& data, glm::vec2& x_bound, glm::vec2& y_bound);
  float evaluate(float x, float y);

  //Subfunction
  Eigen::MatrixXf jacobian(std::vector<glm::vec3>& data);
  void find_number_parameter();

  //Accesseur
  std::vector<float> get_coefficient();
  void set_coefficients(const std::vector<float>& value);
  void set_degree(int degree_x, int degree_y);

private:
  Eigen::VectorXf P;
  int n = 0;
  int m = 0;
  int num_param = 0;
};

}
