#pragma once

#include <memory>
#include <string>

namespace dat::atr{class Node;}
namespace dat::atr{class Structure;}
namespace dat::atr::field{class Manager;}
namespace dat::atr::field{class Operation;}
namespace dat::elm{class Element;}
namespace dat::base{class Entity;}
namespace utl::base{class Element;}


namespace dat::atr::gui{

class Field
{
public:
  //Constructor / Destructor
  Field(dat::atr::Node* node_attribut);
  ~Field();

public:
  //Main function
  void design_header(std::shared_ptr<utl::base::Element> element);

  //Subfunction
  void draw_selection(std::shared_ptr<dat::base::Entity> entity);
  void draw_parameter(std::shared_ptr<dat::base::Entity> entity);

private:
  dat::atr::Structure* atr_struct;
  dat::elm::Element* dat_element;
  dat::atr::field::Manager* atr_field;
  dat::atr::field::Operation* ope_field;

  std::string selected_field = "";
};

}
