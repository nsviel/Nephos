#pragma once

#include <Utility/Specific/Common.h>

namespace dyn::base{class Sensor;}
namespace rad{class Node;}
namespace rad{class Structure;}


namespace rad::detection::glyph{

class Cloud
{
public:
  //Constructor / Destructor
  Cloud(rad::Node* node_radio);
  ~Cloud();

public:
  //Main function
  void create_glyph();
  void draw_sphere_glyph(vec3 pose, float radius);

  //Subfunction
  void reset_glyph();
  void draw_glyph(vec3 pose, float radius);

private:
  rad::Structure* rad_struct;
};

}
