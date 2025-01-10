#pragma once

#include <memory>

namespace dat::atr{class Node;}
namespace dat::atr{class Structure;}
namespace utl::base{class Element;}


namespace dat::atr::gui{

class Normal
{
public:
  //Constructor / Destructor
  Normal(dat::atr::Node* node_attribut);
  ~Normal();

public:
  //Main function
  void design_header(std::shared_ptr<utl::base::Element> element);

  //Subfunction
  void draw_static(std::shared_ptr<utl::base::Element> element);
  void draw_dynamic();

private:
  dat::atr::Structure* atr_struct;
};

}
