#pragma once

#include <Utility/Specific/Common.h>

namespace ope::color{class Heatmap;}
namespace ope::color{class Colormap;}
namespace dat::base{class Entity;}


namespace ope::color{

struct Configuration{
  //---------------------------

  vec4 unicolor;
  vec2 heatmap_range_height;
  float intensity_diviser;
  int color_mode;
  int heatmap_mode;

  //---------------------------
};

enum Mode{
  CAMERA = 0,
  UNICOLOR = 1,
  INTENSITY = 2,
  HEATMAP = 3,
  STRUCTURE = 4,
};

namespace heatmap{
enum Mode{
  INTENSITY = 0,
  HEIGHT = 1,
  RANGE = 2,
};
}

class Colorizer
{
public:
  //Constructor / Destructor
  Colorizer();
  ~Colorizer();

public:
  //Main function
  void make_colorization(dat::base::Entity* entity, ope::color::Configuration& config);

  //Subfunction
  void colorization_unicolor(dat::base::Entity* entity, ope::color::Configuration& config);
  void colorization_intensity(dat::base::Entity* entity, ope::color::Configuration& config);
  void colorization_heatmap(dat::base::Entity* entity, ope::color::Configuration& config);
  void colorization_structure(dat::base::Entity* entity);

private:
  ope::color::Heatmap* ope_heatmap;
  ope::color::Colormap* ope_colormap;
};

}
