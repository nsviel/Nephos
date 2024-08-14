#include "Panel.h"

#include <Transformation/Namespace.h>
#include <Dynamic/Namespace.h>


namespace ope::gui{

//Constructor / Destructor
Panel::Panel(ope::Node* node_operation){
  //---------------------------

  this->gui_color = new ope::gui::Color(node_operation);
  this->gui_transformation = new ope::gui::Transformation();
  this->gui_info = new ope::gui::Info();
  this->gui_operation = new ope::gui::Operation(node_operation);

  //---------------------------
}
Panel::~Panel(){}

//Main function
void Panel::design_panel(utl::base::Element* element){
  //---------------------------

  gui_info->design_info(element);
  gui_transformation->design_transformation(element);
  gui_color->design_colorization(element);
  gui_operation->design_operation(element);

  //---------------------------
}

}
