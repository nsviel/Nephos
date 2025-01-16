#pragma once

#include <memory>

namespace dat::atr{class Node;}
namespace dat::atr{class Structure;}
namespace dat::atr{class Field;}
namespace dat::elm{class Element;}
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
  void draw_selection(std::shared_ptr<utl::base::Element> element);
  void draw_parameter(std::shared_ptr<utl::base::Element> element);

private:
  dat::atr::Structure* atr_struct;
  dat::elm::Element* dat_element;
  dat::atr::Field* atr_field;

  int selection = 0;
};

}
