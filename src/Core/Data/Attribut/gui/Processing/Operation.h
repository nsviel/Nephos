#pragma once

namespace dat::atr{class Node;}
namespace dat::img{class Converter;}
namespace dat::elm{class Element;}
namespace dat::elm{class Image;}
namespace dat::atr::gui{class Normal;}
namespace utl::base{class Element;}



namespace dat::atr::gui{

class Operation
{
public:
  //Constructor / Destructor
  Operation(dat::atr::Node* node_attribut);
  ~Operation();

public:
  //Main function
  void design_operation(std::shared_ptr<utl::base::Element> element);

  //Subfunction
  void draw_img_image(std::shared_ptr<utl::base::Element> element);

private:
  dat::img::Converter* img_image;
  dat::elm::Element* dat_element;
  dat::elm::Image* dat_image;
  dat::atr::gui::Normal* gui_normal;
};

}
