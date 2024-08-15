#pragma once

namespace core{class Node;}
namespace dat::atr{class Node;}
namespace dat::img{class Converter;}
namespace dat::atr::gui{class Normal;}
namespace utl::base{class Element;}
namespace dat::elm{class Element;}


namespace dat::atr::gui{

class Operation
{
public:
  //Constructor / Destructor
  Operation(dat::atr::Node* node_attribut);
  ~Operation();

public:
  //Main function
  void design_operation(utl::base::Element* element);

  //Subfunction
  void draw_img_image(utl::base::Element* element);

private:
  core::Node* node_core;
  dat::img::Converter* img_image;
  dat::elm::Element* dat_element;
  dat::atr::gui::Normal* gui_normal;
};

}
