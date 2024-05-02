#pragma once

#include <Utility/Specific/Common.h>

namespace k4n::dev{class Sensor;}
namespace rad{class Node;}
namespace rad{class Structure;}
namespace rad::detection::cloud{class Glyph;}
namespace k4n::utils{class Transformation;}
namespace ope::fitting{class Sphere;}
namespace ope::fitting{class Ransac;}
namespace ope::attribut{class Normal;}


namespace rad::detection{

enum STEP{
  WAIT_VALIDATION = 0,
  PROCESSING = 1,
};

}

namespace rad{

class Detection
{
public:
  //Constructor / Destructor
  Detection(rad::Node* node_radio);
  ~Detection();

public:
  //Main function
  void next_step(k4n::dev::Sensor* sensor);

  //Subfunction
  void validate_bbox(k4n::dev::Sensor* sensor);
  void ransac_sphere(k4n::dev::Sensor* sensor);

  //Data function
  void data_IfR(vector<vec3>& sphere_xyz, vector<float>& sphere_i);
  void data_IfIt(vector<vec3>& sphere_xyz, vector<float>& sphere_i);
  void data_model(vector<vec3>& sphere_xyz, vector<float>& sphere_i);

  inline string get_step_str(){return map_step[step];}
  inline int get_step(){return step;}

private:
  ope::fitting::Sphere* ope_fitting;
  ope::fitting::Ransac* ope_ransac;
  ope::attribut::Normal* ope_normal;
  rad::detection::cloud::Glyph* radio_glyph;
  k4n::utils::Transformation* k4n_transfo;
  rad::Structure* radio_struct;
  std::map<int, std::string> map_step;

  int step;
  vec3 current_pose;
  float radius;
};

}
