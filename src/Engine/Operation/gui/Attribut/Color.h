#pragma once

namespace ope{class Node;}
namespace ope{class Structure;}
namespace ope::color{class Routine;}
namespace utl::base{class Element;}
namespace dat::base{class Entity;}
namespace utl::base{class Attribut;}


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
  void heatmap_mode(utl::base::Element* element);
  void mode_field_option(utl::base::Element* element);
  void mode_option(utl::base::Element* element);

private:
  ope::Structure* ope_struct;
  ope::color::Routine* ope_colorizer;
  utl::base::Attribut* utl_attribut;
};

}
