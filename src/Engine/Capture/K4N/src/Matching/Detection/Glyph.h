#pragma once

#include <Utility/Specific/common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Sensor;}
namespace k4n::structure{class Circle;}
namespace eng::scene{class Glyph;}


namespace k4n::detection{

class Glyph
{
public:
  //Constructor / Destructor
  Glyph(k4n::Node* node_k4n);
  ~Glyph();

public:
  //Main function
  void draw_all_sphere_glyph(k4n::dev::Sensor* sensor);
  void draw_best_sphere_glyph(k4n::dev::Sensor* sensor);

  //Subfunction
  void reset_all_sphere(k4n::dev::Sensor* sensor);
  void draw_sphere_from_circle(k4n::dev::Sensor* sensor, vector<k4n::structure::Circle>& vec_circle);
  vec3 convert_2d_to_3d(k4n::dev::Sensor* sensor, k4n::structure::Circle& circle);

private:
  eng::scene::Glyph* sce_glyph;
};

}
