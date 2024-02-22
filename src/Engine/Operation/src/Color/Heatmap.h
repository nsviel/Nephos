#pragma once

#include <Utility/Specific/common.h>

namespace ope::color{class Colormap;}
namespace ope::attribut{class Location;}


namespace ope::color{

class Heatmap
{
public:
  //Constructor / Destructor
  Heatmap();
  ~Heatmap();

  //Main function
  void heatmap_intensity(utl::type::Entity* entity, int diviser);
  void heatmap_height(utl::type::Entity* entity);
  void heatmap_height(utl::type::Entity* entity, vec2 range);
  void heatmap_range(utl::type::Entity* entity);

  //Heatmap functions
  void compute_heatmap(vector<float>& v_in, vector<vec4>& heatmap);
  void heatmap_set(utl::type::Entity* entity, vector<float>& v_in);

  inline vec2* get_range_height(){return &range_height;}

private:
  ope::color::Colormap* ope_colormap;
  ope::attribut::Location* ope_location;

  vec2 range_norm;
  vec2 range_height;
  vec2 range_intensity;
  bool is_normalization;
};

}
