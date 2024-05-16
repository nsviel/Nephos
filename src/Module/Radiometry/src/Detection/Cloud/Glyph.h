#pragma once

#include <Utility/Specific/Common.h>

namespace dat::base{class Sensor;}
namespace rad{class Node;}
namespace rad{class Structure;}
namespace dat{class Glyph;}


namespace rad::detection::cloud{

class Glyph
{
public:
  //Constructor / Destructor
  Glyph(rad::Node* node_radio);
  ~Glyph();

public:
  //Main function
  void draw_sphere_glyph(dat::base::Sensor* sensor, vec3 pose, float radius);

  //Subfunction
  void reset_glyph(dat::base::Sensor* sensor);
  void draw_glyph(dat::base::Sensor* sensor, vec3 pose, float radius);

private:
  dat::Glyph* dat_glyph;
  rad::Structure* rad_struct;
};

}
