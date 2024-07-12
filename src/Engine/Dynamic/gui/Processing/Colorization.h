#pragma once

namespace dyn{class Node;}
namespace dyn{class Structure;}
namespace dyn::cloud{class Colorizer;}
namespace utl::base{class Element;}
namespace dat::base{class Entity;}


namespace dyn::gui{

class Colorization
{
public:
  //Constructor / Destructor
  Colorization(dyn::Node* node_dynamic);
  ~Colorization();

public:
  //Main function
  void design_colorization(utl::base::Element* element);
  void update_element(utl::base::Element* element);

  //Mode function
  void colorization_mode(utl::base::Element* element);
  void heatmap_mode(utl::base::Element* element);

  //Option function
  void option_intensity(utl::base::Element* element);
  void option_height(utl::base::Element* element);

private:
  dyn::cloud::Colorizer* dyn_colorizer;
  dyn::Structure* dyn_struct;

  bool update_color = false;
};

}
