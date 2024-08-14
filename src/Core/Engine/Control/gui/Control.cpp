#include "Control.h"

#include <Control/Namespace.h>


namespace ctr::gui{

//Constructor / Destructor
Control::Control(ctr::Node* node_control){
  //---------------------------

  this->ctr_struct = node_control->get_ctr_struct();
  this->gui_navigation = new ctr::gui::Navigation(node_control);
  this->gui_edition = new ctr::gui::Edition(node_control);
  this->gui_player = new ctr::gui::Player(node_control);
  this->gui_render = new ctr::gui::Render(node_control);

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
