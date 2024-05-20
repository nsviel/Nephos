#include "Node.h"

#include <Engine/Namespace.h>
#include <Camera/Namespace.h>
#include <Utility/Namespace.h>
#include <Data/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace cam{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  utl::gui::Panel* cam_panel = add_panel("Camera", ICON_FA_CAMERA, false);
  //---------------------------

  //Dependancy
  this->node_vulkan = node_engine->get_node_vulkan();
  this->node_data = node_engine->get_node_data();

  //Child
  this->cam_struct = new cam::Structure();
  this->cam_control = new cam::Control(this);
  this->cam_manager = new cam::Manager(this);
  this->cam_pather = new cam::Pather(this);
  this->gui_control = new cam::gui::Control(this);
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
