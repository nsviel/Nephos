#include "Control.h"

#include <Interface/Namespace.h>


namespace ctl::gui{

//Constructor / Destructor
Control::Control(itf::Node* node_interface){
  //---------------------------

  this->itf_struct = node_interface->get_ctl_struct();
  this->gui_navigation = new ctl::gui::Navigation(node_interface);
  this->gui_edition = new ctl::gui::Edition(node_interface);
  this->gui_player = new itf::gui::Player(node_interface);
  this->gui_render = new itf::gui::Render(node_interface);

  //---------------------------
}
Control::~Control(){}

//Main function
void Control::run_control(){
  //---------------------------

  gui_render->run_control();
  gui_player->run_control();
  gui_edition->run_control();
  gui_navigation->run_control();

  //---------------------------
}

}
