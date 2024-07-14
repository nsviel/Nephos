#include "Panel.h"

#include <Operation/Namespace.h>


namespace ope::gui{

//Constructor / Destructor
Panel::Panel(dyn::Node* node_dynamic, bool* show_window){
  //---------------------------

  this->gui_colorization = new ope::gui::Colorization(node_dynamic);
  this->gui_transformation = new ope::gui::Transformation(node_dynamic);
  this->gui_information = new ope::gui::Info(node_dynamic);
  this->gui_configuration = new ope::gui::Configuration(node_dynamic);
  this->gui_normal = new ope::gui::Normal(node_dynamic);

  //---------------------------
}
Panel::~Panel(){}

//Main function
void Panel::design_panel(utl::base::Element* element){
  //---------------------------

  gui_information->design_info(element);
  gui_configuration->design_configuration(element);
  gui_transformation->design_transformation(element);
  gui_colorization->design_colorization(element);
  gui_normal->design_normal();

  //---------------------------
}

}
