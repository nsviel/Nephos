#pragma once

#include <Utility/Specific/common.h>

namespace eng::ope{class Heatmap;}


namespace ope::color{

class Colorization
{
public:
  //Constructor / Destructor
  Colorization();
  ~Colorization();

public:
  //Main function
  void make_colorization(utl::type::Data* data, int color_mode, int heatmap_mode);

  //Subfunction
  void colorization_unicolor(utl::type::Data* data);
  void colorization_intensity(utl::type::Data* data);
  void colorization_heatmap(utl::type::Data* data, int heatmap_mode);
  void colorization_structure(utl::type::Data* data);

private:
  eng::ope::Heatmap* ope_heatmap;
};

}
