#pragma once

namespace ope{class Node;}
namespace ope{class Structure;}
namespace ope::color{class Routine;}
namespace utl::base{class Element;}
namespace dat::base{class Entity;}


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
  void option_intensity(utl::base::Element* element);
  void option_height(utl::base::Element* element);

private:
  ope::Structure* ope_struct;
  ope::color::Routine* ope_colorizer;
};

}
