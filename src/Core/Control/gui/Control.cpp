#include "Control.h"

#include <Control/Namespace.h>


namespace ctl::gui{

//Constructor / Destructor
Control::Control(ctl::Node* node_control){
  //---------------------------

  this->ctl_struct = node_control->get_ctl_struct();
  this->gui_navigation = new ctl::gui::Navigation(node_control);
  this->gui_edition = new ctl::gui::Edition(node_control);
  this->gui_player = new ctl::gui::Player(node_control);
  this->gui_render = new ctl::gui::Render(node_control);

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
