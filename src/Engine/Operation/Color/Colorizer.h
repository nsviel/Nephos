#pragma once

#include <Operation/Color/Structure/Configuration.h>
#include <glm/glm.hpp>

namespace ope::color{class Heatmap;}
namespace ope::color{class Colormap;}
namespace dat::base{class Entity;}
namespace utl::base{class Attribut;}


namespace ope::color{

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
  void colorization_intensity_cor(dat::base::Entity* entity, ope::color::Configuration& config);
  void colorization_intensity_cal(dat::base::Entity* entity, ope::color::Configuration& config);
  void colorization_incidence_angle(dat::base::Entity* entity, ope::color::Configuration& config);
  void colorization_normal(dat::base::Entity* entity, ope::color::Configuration& config);
  void colorization_location(dat::base::Entity* entity, ope::color::Configuration& config);
  void colorization_heatmap(dat::base::Entity* entity, ope::color::Configuration& config);
  void colorization_structure(dat::base::Entity* entity);

private:
  ope::color::Heatmap* ope_heatmap;
  ope::color::Colormap* ope_colormap;
  utl::base::Attribut* utl_attribut;
};

}
