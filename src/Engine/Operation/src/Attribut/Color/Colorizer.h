#pragma once

#include <Utility/Element/Color/Namespace.h>
#include <glm/glm.hpp>

namespace ope{class Node;}
namespace ope{class Structure;}
namespace ope::color{class Heatmap;}
namespace utl::base{class Attribut;}
namespace utl::base{class Element;}
namespace dat::base{class Entity;}
namespace dat::base{class Set;}


namespace ope::color{

class Colorizer
{
public:
  //Constructor / Destructor
  Colorizer(ope::Node* node_operation);
  ~Colorizer();

public:
  //Main function
  void make_colorization(utl::base::Element* element);
  void make_colorization(dat::base::Set* set);
  void make_colorization(dat::base::Entity* entity);

  //Subfunction
  void colorization_rgb(dat::base::Entity* entity);
  void colorization_unicolor(dat::base::Entity* entity);
  void colorization_normal(dat::base::Entity* entity);
  void colorization_field(dat::base::Entity* entity);
  void colorization_structure(dat::base::Entity* entity);
  void colorization_heatmap(dat::base::Entity* entity);

private:
  ope::Structure* ope_struct;
  ope::color::Heatmap* ope_heatmap;
  utl::base::Attribut* utl_attribut;
};

}
