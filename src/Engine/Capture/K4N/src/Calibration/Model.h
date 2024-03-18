#pragma once

#include <Utility/Specific/common.h>

namespace k4n{class Node;}
namespace ope::attribut{class Fitting;}


namespace k4n::calibration{

class Model
{
public:
  //Constructor / Destructor
  Model(k4n::Node* node_k4n);
  ~Model();

public:
  //Main function

  inline float* get_sphere_diameter(){return &sphere_diameter;}

private:
  ope::attribut::Fitting* ope_fitting;
  float sphere_diameter = 10;
};

}
