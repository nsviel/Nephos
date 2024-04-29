#pragma once

#include <Utility/Specific/Common.h>

namespace k4n::dev{class Sensor;}
namespace radio{class Structure;}
namespace gly{class Node;}


namespace radio::detection::cloud{

class Glyph
{
public:
  //Constructor / Destructor
  Glyph(radio::Structure* radio_struct);
  ~Glyph();

public:
  //Main function
  void draw_sphere_glyph(k4n::dev::Sensor* sensor, vec3 pose, float radius);

  //Subfunction
  void reset_glyph(k4n::dev::Sensor* sensor);
  void draw_glyph(k4n::dev::Sensor* sensor, vec3 pose, float radius);

private:
  gly::Node* sce_glyph;
};

}
