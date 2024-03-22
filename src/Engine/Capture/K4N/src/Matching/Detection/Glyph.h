#pragma once

#include <Utility/Specific/common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Swarm;}
namespace k4n::dev{class Sensor;}
namespace k4n::detection{class Hough;}
namespace k4n::matching{class Image;}
namespace ope::attribut{class Fitting;}
namespace eng::scene{class Glyph;}
namespace eng{class Node;}
namespace glyph::scene{class Sphere;}


namespace k4n::detection{

class Glyph
{
public:
  //Constructor / Destructor
  Glyph(k4n::Node* node_k4n);
  ~Glyph();

public:
  //Main function
  void draw_glyph_in_cloud(k4n::dev::Sensor* sensor);

  //Subfunction
  void reset_all_sphere(k4n::dev::Sensor* sensor);
  void draw_all_sphere(k4n::dev::Sensor* sensor);

private:
  eng::scene::Glyph* sce_glyph;
};

}
