#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace ope::color{class Colormap;}
namespace ope::attribut{class Location;}
namespace dat::base{class Entity;}

using namespace glm;


namespace ope::color{

class Heatmap
{
public:
  //Constructor / Destructor
  Heatmap();
  ~Heatmap();

  //Main function
  void heatmap_intensity(dat::base::Entity* entity, int diviser);
  void heatmap_height(dat::base::Entity* entity);
  void heatmap_height(dat::base::Entity* entity, vec2 range);
  void heatmap_range(dat::base::Entity* entity);

  //Heatmap functions
  void compute_heatmap(std::vector<float>& v_in, std::vector<glm::vec4>& heatmap);
  void heatmap_set(dat::base::Entity* entity, std::vector<float>& v_in);

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
