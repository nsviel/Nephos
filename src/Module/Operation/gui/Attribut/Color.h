#pragma once

namespace ope{class Node;}
namespace ope{class Structure;}
namespace ope::attribut{class Color;}
namespace utl::base{class Element;}
namespace utl::base{class Attribut;}
namespace dat::base{class Entity;}
namespace dat{class Element;}


namespace ope::gui{

class Color
{
public:
  //Constructor / Destructor
  Color(ope::Node* node_dynamic);
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
  ope::Structure* ope_struct;
  ope::attribut::Color* ope_color;
  utl::base::Attribut* utl_attribut;
  dat::Element* dat_element;
};

}
