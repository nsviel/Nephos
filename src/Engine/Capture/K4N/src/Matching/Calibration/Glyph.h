#pragma once

#include <Utility/Specific/common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Sensor;}
namespace k4n::structure{class Circle;}
namespace k4n::utils{class Transformation;}
namespace eng::scene{class Glyph;}


namespace k4n::calibration{

class Glyph
{
public:
  //Constructor / Destructor
  Glyph(k4n::Node* node_k4n);
  ~Glyph();

public:
  //Main function
  void draw_sphere_glyph(k4n::dev::Sensor* sensor);

private:
  k4n::utils::Transformation* k4n_transfo;
  eng::scene::Glyph* sce_glyph;
};

}
