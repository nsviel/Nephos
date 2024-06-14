#pragma once

#include <glm/glm.hpp>

namespace ope::color{class Heatmap;}
namespace ope::color{class Colormap;}
namespace dat::base{class Entity;}


namespace ope::color{

struct Configuration{
  //---------------------------

  glm::vec4 unicolor;
  glm::vec2 heatmap_range_height;
  float intensity_diviser;
  int color_mode;
  int heatmap_mode;

  //---------------------------
};

enum Mode{
  RGB = 0,
  UNICOLOR = 1,
  INTENSITY = 2,
  INTENSITY_INV = 3,
  NORMAL = 4,
  HEATMAP = 5,
  STRUCTURE = 6,
};

namespace heatmap{
enum Mode{
  INTENSITY = 0,
  HEIGHT = 2,
  RANGE = 3,
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
  void colorization_rgb(dat::base::Entity* entity, ope::color::Configuration& config);
  void colorization_unicolor(dat::base::Entity* entity, ope::color::Configuration& config);
  void colorization_intensity(dat::base::Entity* entity, ope::color::Configuration& config);
  void colorization_intensity_inv(dat::base::Entity* entity, ope::color::Configuration& config);
  void colorization_normal(dat::base::Entity* entity, ope::color::Configuration& config);
  void colorization_heatmap(dat::base::Entity* entity, ope::color::Configuration& config);
  void colorization_structure(dat::base::Entity* entity);

private:
  ope::color::Heatmap* ope_heatmap;
  ope::color::Colormap* ope_colormap;
};

}
