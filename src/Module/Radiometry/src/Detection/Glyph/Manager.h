#pragma once

#include <Utility/Specific/Common.h>

namespace dyn::base{class Sensor;}
namespace rad{class Node;}
namespace rad{class Structure;}
namespace rad::detection::structure{class Circle;}
namespace dat{class Glyph;}
namespace eng{class Node;}


namespace rad::detection::glyph{

class Manager
{
public:
  //Constructor / Destructor
  Manager(rad::Node* node_radio);
  ~Manager();

public:
  //Main function
  void create_sphere_glyph();
  void draw_calibration_sphere(vec3 pose, float radius);

  void draw_detected_sphere(dyn::base::Sensor* sensor);
  void draw_all_sphere_glyph(dyn::base::Sensor* sensor);
  void draw_best_sphere_glyph(dyn::base::Sensor* sensor);

  //Subfunction
  void reset_all_sphere();
  void draw_sphere_from_circle(dyn::base::Sensor* sensor, vector<rad::detection::structure::Circle>& vec_circle);

private:
  eng::Node* node_engine;
  rad::Structure* rad_struct;
  dat::Glyph* dat_glyph;
};

}
