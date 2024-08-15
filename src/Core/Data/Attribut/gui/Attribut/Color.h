#pragma once

namespace dat::atr{class Node;}
namespace dat::atr{class Structure;}
namespace dat::atr{class Color;}
namespace utl::base{class Element;}
namespace utl::base{class Attribut;}
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
  void design_colorization(utl::base::Element* element);

  //Subfunction
  void color_mode(utl::base::Element* element);
  void color_mode_rgb(utl::base::Element* element);
  void color_mode_unicolor(utl::base::Element* element);
  void color_mode_normal(utl::base::Element* element);
  void color_mode_field(utl::base::Element* element);
  void color_mode_heatmap(utl::base::Element* element);
  void color_mode_structure(utl::base::Element* element);
  void color_option(utl::base::Element* element);

private:
  dat::atr::Structure* atr_struct;
  dat::atr::Color* atr_color;
  utl::base::Attribut* utl_attribut;
  dat::elm::Element* dat_element;
};

}
