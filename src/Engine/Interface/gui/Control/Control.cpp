#include "Control.h"

#include <Interface/Namespace.h>


namespace itf::gui{

//Constructor / Destructor
Control::Control(itf::Node* node_interface){
  //---------------------------

  this->itf_struct = node_interface->get_itf_struct();
  this->gui_navigation = new itf::gui::Navigation(node_interface);
  this->gui_edition = new itf::gui::Edition(node_interface);
  this->gui_player = new itf::gui::Player(node_interface);

  //---------------------------
}
Control::~Control(){}

//Main function
void Control::run_control(glm::vec2 center){
  //---------------------------

  gui_player->run_control();
  gui_edition->run_control();
  gui_navigation->run_control(center);

  //---------------------------
}

}
