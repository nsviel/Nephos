#pragma once

#include <Utility/Specific/Common.h>

namespace k4n::dev{class Sensor;}
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
  void draw_sphere_glyph(k4n::dev::Sensor* sensor, vec3 pose, float radius);

  //Subfunction
  void reset_glyph(k4n::dev::Sensor* sensor);
  void draw_glyph(k4n::dev::Sensor* sensor, vec3 pose, float radius);

private:
  dat::Glyph* dat_glyph;
};

}
