#pragma once

#include <Utility/Specific/Common.h>

namespace dyn::base{class Sensor;}
namespace rad::detection{class Node;}
namespace rad::detection{class Structure;}
namespace rad::detection::structure{class Circle;}
namespace dat{class Glyph;}
namespace eng{class Node;}


namespace rad::detection::sphere{

class Glyph
{
public:
  //Constructor / Destructor
  Glyph(rad::detection::Node* node_detection);
  ~Glyph();

public:
  //Main function
  void create_sphere_glyph();

  //Subfunction
  void draw_calibration_sphere(dyn::base::Sensor* sensor);
  void draw_detection_sphere(dyn::base::Sensor* sensor);
  void draw_sphere_glyph(dyn::base::Sensor* sensor, vector<rad::detection::structure::Circle>& vec_circle);

  //Reset function
  void reset_all_sphere();
  void reset_detection_sphere();

private:
  eng::Node* node_engine;
  rad::detection::Structure* rad_struct;
  dat::Glyph* dat_glyph;
};

}
