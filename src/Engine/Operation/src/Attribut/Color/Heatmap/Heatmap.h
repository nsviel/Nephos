#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace ope::attribut{class Location;}
namespace dat::base{class Entity;}
namespace utl::base{class Attribut;}


namespace ope::color{

class Heatmap
{
public:
  //Constructor / Destructor
  Heatmap();
  ~Heatmap();

  //Main function
  void heatmap_intensity(dat::base::Entity* entity, int diviser);
  void heatmap_intensity_cor(dat::base::Entity* entity);
  void heatmap_intensity_cal(dat::base::Entity* entity);
  void heatmap_incidence_angle(dat::base::Entity* entity);
  void heatmap_height(dat::base::Entity* entity);
  void heatmap_height(dat::base::Entity* entity, glm::vec2 range);
  void heatmap_range(dat::base::Entity* entity);

  //Heatmap functions
  void compute_heatmap(std::vector<float>& v_in, std::vector<glm::vec4>& rgba);

  inline glm::vec2* get_range_height(){return &range_height;}

private:
  ope::attribut::Location* ope_location;
  utl::base::Attribut* utl_attribut;

  glm::vec2 range_norm;
  glm::vec2 range_height;
  glm::vec2 range_intensity;
  bool is_normalization;
};

}
