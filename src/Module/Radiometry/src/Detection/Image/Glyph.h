#pragma once

#include <Utility/Specific/Common.h>

namespace dat::base{class Sensor;}
namespace rad{class Node;}
namespace rad{class Structure;}
namespace rad::detection::structure{class Circle;}
namespace dat{class Glyph;}


namespace rad::detection::image{

class Glyph
{
public:
  //Constructor / Destructor
  Glyph(rad::Node* node_radio);
  ~Glyph();

public:
  //Main function
  void draw_detected_sphere(dat::base::Sensor* sensor);
  void draw_all_sphere_glyph(dat::base::Sensor* sensor);
  void draw_best_sphere_glyph(dat::base::Sensor* sensor);

  //Subfunction
  void reset_all_sphere();
  void draw_sphere_from_circle(dat::base::Sensor* sensor, vector<rad::detection::structure::Circle>& vec_circle);

private:
  dat::Glyph* dat_glyph;
  rad::Structure* rad_struct;
};

}
