#pragma once

#include <Utility/Specific/Common.h>

namespace dyn::base{class Sensor;}
namespace rad{class Node;}
namespace rad::detection{class Structure;}
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

  //Subfunction
  void draw_calibration_sphere(dyn::base::Sensor* sensor, float radius);
  void draw_detection_sphere(dyn::base::Sensor* sensor);
  void reset_detection_sphere();
  void draw_detection_sphere(dyn::base::Sensor* sensor, vector<rad::detection::structure::Circle>& vec_circle);

private:
  eng::Node* node_engine;
  rad::detection::Structure* rad_struct;
  dat::Glyph* dat_glyph;
};

}
