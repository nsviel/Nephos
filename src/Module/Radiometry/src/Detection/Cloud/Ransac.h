#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad{class Structure;}
namespace dat::base{class Sensor;}

namespace rad::detection::cloud{class Glyph;}
namespace ope::fitting{class Sphere;}
namespace ope::fitting{class Ransac;}
namespace ope::attribut{class Normal;}


namespace rad::detection::cloud{

class Ransac
{
public:
  //Constructor / Destructor
  Ransac(rad::Node* node_radio);
  ~Ransac();

public:
  //Main function
  void validate_bbox(dat::base::Sensor* sensor);
  void ransac_sphere(dat::base::Sensor* sensor);

  //Data function
  void data_IfR(vector<vec3>& sphere_xyz, vector<float>& sphere_i);
  void data_IfIt(vector<vec3>& sphere_xyz, vector<float>& sphere_i);
  void data_model(vector<vec3>& sphere_xyz, vector<float>& sphere_i);

private:

  rad::Structure* rad_struct;
  rad::detection::cloud::Glyph* rad_glyph;
  ope::fitting::Sphere* ope_fitting;
  ope::fitting::Ransac* ope_ransac;
  ope::attribut::Normal* ope_normal;

  vec3 current_pose;
  float radius;
};

}
