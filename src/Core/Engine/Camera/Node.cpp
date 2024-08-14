#include "Node.h"

#include <Core/Namespace.h>
#include <Data/Namespace.h>
#include <Camera/Namespace.h>
#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace cam{

//Constructor / Destructor
Node::Node(core::Node* node_core){
  utl::gui::Panel* cam_panel = add_panel("Camera", ICON_FA_CAMERA, false);
  //---------------------------

  //Dependancy
  this->node_vulkan = node_core->get_node_vulkan();
  this->node_data = node_core->get_node_data();

  //Child
  this->cam_struct = new cam::Structure();
  this->cam_control = new cam::Control(this);
  this->cam_manager = new cam::Manager(this);
  this->cam_pather = new cam::Pather(this);
  this->gui_panel = new cam::gui::Panel(this, &cam_panel->is_open);

  //---------------------------
}
Node::~Node(){
  //---------------------------

  delete cam_manager;
  delete cam_control;

  //---------------------------
}

//Main function
void Node::init(){
  //---------------------------

  cam_manager->create_camera();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  cam_control->control_mouse();
  cam_pather->loop();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  gui_panel->run_panel();

  //---------------------------
}
void Node::reset(){
  //---------------------------

  cam_manager->reset_camera();

  //---------------------------
}


}
