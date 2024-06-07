#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad{class Structure;}
namespace dyn::base{class Sensor;}

namespace rad::detection::glyph{class Manager;}
namespace ope::fitting{class Sphere;}
namespace ope::fitting{class Ransac;}


namespace rad::detection::cloud{

class Ransac
{
public:
  //Constructor / Destructor
  Ransac(rad::Node* node_radio);
  ~Ransac();

public:
  //Main function
  void ransac_sphere(dyn::base::Sensor* sensor);

  //Subfunction
  void reduce_search_space(dyn::base::Sensor* sensor, vector<vec3>& search_xyz, vector<float>& search_is);
  void apply_ransac(vector<vec3>& search_xyz, vector<float>& search_is);
  void process_result(vector<vec3>& search_xyz, vector<float>& search_is);

  //Data function
  void data_IfR(vector<vec3>& sphere_xyz, vector<float>& sphere_i);
  void data_IfIt(vector<vec3>& sphere_xyz, vector<float>& sphere_i);
  void data_model(vector<vec3>& sphere_xyz, vector<float>& sphere_i);

private:

  rad::Structure* rad_struct;
  rad::detection::glyph::Manager* rad_glyph;
  ope::fitting::Sphere* ope_fitting;
  ope::fitting::Ransac* ope_ransac;

  vec3 current_pose;
  float radius;
};

}
