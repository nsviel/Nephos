#pragma once

namespace ope{class Node;}
namespace ope{class Structure;}
namespace ope::color{class Routine;}
namespace utl::base{class Element;}
namespace dat::base{class Entity;}


namespace ope::gui{

class Colorization
{
public:
  //Constructor / Destructor
  Colorization(ope::Node* node_dynamic);
  ~Colorization();

public:
  //Main function
  void design_colorization(utl::base::Element* element);

  //Mode function
  void colorization_mode(utl::base::Element* element);
  void heatmap_mode(utl::base::Element* element);

  //Option function
  void option_intensity(utl::base::Element* element);
  void option_height(utl::base::Element* element);

private:
  ope::Structure* ope_struct;
  ope::color::Routine* ope_colorizer;
};

}
