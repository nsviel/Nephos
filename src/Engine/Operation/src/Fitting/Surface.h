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
  float evaluate(float x, float y);

  //Subfunction
  Eigen::MatrixXf jacobian(vector<vec3>& data);

private:
  Eigen::VectorXf P;
  int degree = 0;
};

}
