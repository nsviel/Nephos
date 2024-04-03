#pragma once

#include <Utility/Specific/Common.h>


namespace ope::fitting{

class Surface
{
public:
  Surface();
  ~Surface();

public:
  //Main function
  void compute(vector<vec3>& data);
  void compute(vector<vec3>& data, vec2& x_bound, vec2& y_bound);
  float evaluate(float x, float y);

  //Subfunction
  Eigen::MatrixXf jacobian(vector<vec3>& data);
  vector<float> get_coefficient();
  void find_number_parameter();
  void set_coefficients(const std::vector<float>& value);
  void set_degree(int degree_x, int degree_y);

private:
  Eigen::VectorXf P;
  int n = 0;
  int m = 0;
  int num_param = 0;
};

}
