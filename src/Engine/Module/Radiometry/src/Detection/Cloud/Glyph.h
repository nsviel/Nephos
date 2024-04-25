#pragma once

#include <Utility/Specific/Common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Sensor;}
namespace k4n::structure{class Circle;}
namespace k4n::utils{class Transformation;}
namespace eng::scene{class Glyph;}


namespace radio::calibration{

class Glyph
{
public:
  //Constructor / Destructor
  Glyph(k4n::Node* node_k4n);
  ~Glyph();

public:
  //Main function
  void draw_sphere_glyph(k4n::dev::Sensor* sensor, vec3 pose, float radius);

  //Subfunction
  void reset_glyph(k4n::dev::Sensor* sensor);
  void draw_glyph(k4n::dev::Sensor* sensor, vec3 pose, float radius);

private:
  k4n::utils::Transformation* k4n_transfo;
  eng::scene::Glyph* sce_glyph;
};

}
