#pragma once

#include <Utility/Specific/Common.h>

namespace k4n::dev{class Sensor;}
namespace radio{class Structure;}
namespace radio::structure{class Circle;}
namespace k4n::utils{class Transformation;}
namespace gly{class Node;}


namespace radio::detection{

class Glyph
{
public:
  //Constructor / Destructor
  Glyph(radio::Structure* radio_struct);
  ~Glyph();

public:
  //Main function
  void draw_all_sphere_glyph(k4n::dev::Sensor* sensor);
  void draw_best_sphere_glyph(k4n::dev::Sensor* sensor);

  //Subfunction
  void reset_all_sphere(k4n::dev::Sensor* sensor);
  void draw_sphere_from_circle(k4n::dev::Sensor* sensor, vector<radio::structure::Circle>& vec_circle);

private:
  k4n::utils::Transformation* k4n_transfo;
  gly::Node* node_glyph;
};

}
