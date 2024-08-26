#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace dat::atr{class Node;}
namespace dat::atr{class Structure;}
namespace dat::atr{class Field;}
namespace utl::base{class Element;}
namespace dat::base{class Entity;}
namespace dat::base{class Set;}


namespace dat::atr{

class Heatmap
{
public:
  //Constructor / Destructor
  Heatmap(dat::atr::Node* node_attribut);
  ~Heatmap();

public:
  //Main function
  void colorization_heatmap(std::shared_ptr<dat::base::Entity> entity);

  //Subfunction
  void compute_heatmap(std::vector<float>& v_in, std::vector<glm::vec4>& rgba);

private:
  dat::atr::Structure* atr_struct;
  dat::atr::Field* atr_field;
};

}
