#pragma once

#include <glm/glm.hpp>

namespace dat::atr{class Node;}
namespace dat::atr{class Structure;}
namespace dat::atr{class Heatmap;}
namespace utl::base{class Attribut;}
namespace utl::base{class Element;}
namespace dat::base{class Entity;}
namespace dat::base{class Set;}


namespace dat::atr{

class Color
{
public:
  //Constructor / Destructor
  Color(dat::atr::Node* node_attribut);
  ~Color();

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

private:
  dat::atr::Structure* atr_struct;
  dat::atr::Heatmap* atr_heatmap;
  utl::base::Attribut* utl_attribut;
};

}
