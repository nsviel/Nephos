#pragma once

namespace eng{class Node;}
namespace ope{class Node;}
namespace ope::image{class Converter;}
namespace ope::gui{class Normal;}
namespace utl::base{class Element;}
namespace dat{class Element;}


namespace ope::gui{

class Operation
{
public:
  //Constructor / Destructor
  Operation(ope::Node* node_operation);
  ~Operation();

public:
  //Main function
  void design_operation(utl::base::Element* element);

  //Subfunction
  void draw_ope_image(utl::base::Element* element);

private:
  eng::Node* node_engine;
  ope::image::Converter* ope_image;
  dat::Element* dat_element;
  ope::gui::Normal* gui_normal;
};

}