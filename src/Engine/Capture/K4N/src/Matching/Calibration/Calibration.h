#pragma once

#include <Utility/Specific/common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Sensor;}
namespace k4n::structure{class K4N;}
namespace k4n::calibration{class Glyph;}
namespace k4n::utils{class Transformation;}
namespace ope::attribut{class Fitting;}


namespace k4n::calibration{

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
  void validate_bbox(k4n::dev::Sensor* sensor);
  void ransac_sphere(k4n::dev::Sensor* sensor);

  inline string get_step_str(){return map_step[step];}

private:
  ope::attribut::Fitting* ope_fitting;
  k4n::calibration::Glyph* k4n_glyph;
  k4n::utils::Transformation* k4n_transfo;
  k4n::structure::K4N* k4n_struct;
  std::map<int, std::string> map_step;

  int step;
  ivec2 point_2d;
  vec3 point_3d;
  float radius;
};

}
