#pragma once

#include <Utility/Specific/common.h>

namespace eng::ope{class Heatmap;}


namespace ope::color{

struct Configuration{
  //---------------------------

  int color_mode;
  int heatmap_mode;
  vec2 heatmap_range_height;
  float intensity_division;

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

class Colorization
{
public:
  //Constructor / Destructor
  Colorization();
  ~Colorization();

public:
  //Main function
  void make_colorization(utl::type::Entity* entity, ope::color::Configuration& config);

  //Subfunction
  void colorization_unicolor(utl::type::Entity* entity);
  void colorization_intensity(utl::type::Entity* entity, ope::color::Configuration& config);
  void colorization_heatmap(utl::type::Entity* entity, ope::color::Configuration& config);
  void colorization_structure(utl::type::Entity* entity);

private:
  eng::ope::Heatmap* ope_heatmap;
};

}
