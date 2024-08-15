#include "Panel.h"

#include <Attribut/Namespace.h>
#include <Dynamic/Namespace.h>


namespace dat::atr::gui{

//Constructor / Destructor
Panel::Panel(dat::atr::Node* node_attribut){
  //---------------------------

  this->gui_color = new dat::atr::gui::Color(node_attribut);
  this->gui_transformation = new dat::atr::gui::Transformation();
  this->gui_info = new dat::atr::gui::Info();
  this->gui_operation = new dat::atr::gui::Operation(node_attribut);

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
