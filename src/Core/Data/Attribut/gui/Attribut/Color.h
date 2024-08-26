#pragma once

#include <memory>

namespace dat::atr{class Node;}
namespace dat::atr{class Structure;}
namespace dat::atr{class Color;}
namespace utl::base{class Element;}
namespace dat::atr{class Field;}
namespace dat::base{class Entity;}
namespace dat::elm{class Element;}


namespace dat::atr::gui{

class Color
{
public:
  //Constructor / Destructor
  Color(dat::atr::Node* node_attribut);
  ~Color();

public:
  //Main function
  void design_colorization(std::shared_ptr<utl::base::Element> element);

  //Subfunction
  void color_mode(std::shared_ptr<utl::base::Element> element);
  void color_mode_rgb(std::shared_ptr<utl::base::Element> element);
  void color_mode_unicolor(std::shared_ptr<utl::base::Element> element);
  void color_mode_normal(std::shared_ptr<utl::base::Element> element);
  void color_mode_field(std::shared_ptr<utl::base::Element> element);
  void color_mode_heatmap(std::shared_ptr<utl::base::Element> element);
  void color_mode_structure(std::shared_ptr<utl::base::Element> element);
  void color_option(std::shared_ptr<utl::base::Element> element);

private:
  dat::atr::Structure* atr_struct;
  dat::atr::Color* atr_color;
  dat::atr::Field* atr_field;
  dat::elm::Element* dat_element;
};

}
