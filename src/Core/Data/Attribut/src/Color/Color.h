#pragma once

#include <glm/glm.hpp>
#include <memory>

namespace dat::atr{class Node;}
namespace dat::atr{class Structure;}
namespace dat::atr{class Heatmap;}
namespace dat::atr{class Field;}
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
  void make_colorization(const std::shared_ptr<utl::base::Element> element);
  void make_colorization(const std::shared_ptr<dat::base::Set> set);
  void make_colorization(const std::shared_ptr<dat::base::Entity> entity);

  //Subfunction
  void colorization_rgb(std::shared_ptr<dat::base::Entity> entity);
  void colorization_unicolor(std::shared_ptr<dat::base::Entity> entity);
  void colorization_normal(std::shared_ptr<dat::base::Entity> entity);
  void colorization_field(std::shared_ptr<dat::base::Entity> entity);
  void colorization_structure(std::shared_ptr<dat::base::Entity> entity);

private:
  dat::atr::Structure* atr_struct;
  dat::atr::Heatmap* atr_heatmap;
  dat::atr::Field* atr_field;
};

}
