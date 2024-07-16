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
  void compute_heatmap(std::vector<float>& v_in, std::vector<glm::vec4>& rgba);

private:
};

}
