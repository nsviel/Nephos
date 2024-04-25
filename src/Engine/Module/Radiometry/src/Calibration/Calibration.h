#pragma once

#include <Utility/Specific/Common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Sensor;}
namespace k4n::structure{class K4N;}
namespace radio::calibration{class Glyph;}
namespace k4n::utils{class Transformation;}
namespace ope::fitting{class Sphere;}
namespace ope::fitting{class Ransac;}
namespace ope::attribut{class Normal;}


namespace radio::calibration{

enum STEP{
  WAIT_VALIDATION = 0,
  PROCESSING = 1,
};

class Calibration
{
public:
  //Constructor / Destructor
  Calibration(k4n::Node* node_k4n);
  ~Calibration();

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
  radio::calibration::Glyph* k4n_glyph;
  k4n::utils::Transformation* k4n_transfo;
  k4n::structure::K4N* k4n_struct;
  std::map<int, std::string> map_step;

  int step;
  vec3 current_pose;
  float radius;
};

}
