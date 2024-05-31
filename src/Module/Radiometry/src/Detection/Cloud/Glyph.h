#pragma once

#include <Utility/Specific/Common.h>

namespace dat::base{class Sensor;}
namespace rad{class Node;}
namespace rad{class Structure;}


namespace rad::detection::cloud{

class Glyph
{
public:
  //Constructor / Destructor
  Glyph(rad::Node* node_radio);
  ~Glyph();

public:
  //Main function
  void draw_sphere_glyph(vec3 pose, float radius);

  //Subfunction
  void reset_glyph();
  void draw_glyph(vec3 pose, float radius);

private:
  rad::Structure* rad_struct;
};

}
