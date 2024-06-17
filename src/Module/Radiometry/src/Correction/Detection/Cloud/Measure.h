#pragma once

#include <Utility/Specific/Common.h>

namespace rad::correction{class Node;}
namespace rad::correction{class Structure;}


namespace rad::correction::cloud{

class Measure
{
public:
  //Constructor / Destructor
  Measure(rad::correction::Node* node_correction);
  ~Measure();

public:
  //Main function
  void process_measure();

  //Subfunction
  void data_measure(vector<vec3>& sphere_xyz, vector<float>& sphere_i);
  void data_IfR(vector<vec3>& sphere_xyz, vector<float>& sphere_i);
  void data_IfIt(vector<vec3>& sphere_xyz, vector<float>& sphere_i);

private:
  rad::correction::Structure* rad_struct;
};

}
