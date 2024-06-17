#pragma once

#include <Utility/Specific/Common.h>

namespace rad::detection{class Node;}
namespace rad::model{class Structure;}
namespace rad::detection{class Structure;}


namespace rad::detection::cloud{

class Measure
{
public:
  //Constructor / Destructor
  Measure(rad::detection::Node* node_detection);
  ~Measure();

public:
  //Main function
  void process_measure();

  //Subfunction
  void data_measure(vector<vec3>& sphere_xyz, vector<float>& sphere_i);
  void data_IfR(vector<vec3>& sphere_xyz, vector<float>& sphere_i);
  void data_IfIt(vector<vec3>& sphere_xyz, vector<float>& sphere_i);

private:
  rad::model::Structure* model_struct;
  rad::detection::Structure* rad_struct;
};

}
