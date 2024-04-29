#include "Node.h"

#include <Engine/Namespace.h>
#include <Camera/Namespace.h>
#include <Utility/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace cam{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  utl::gui::Panel* cam_panel = add_panel("Camera", ICON_FA_CAMERA, false);
  //---------------------------

  //Dependancy
  this->node_vulkan = node_engine->get_node_vulkan();
  this->node_engine = node_engine;

  //Child
  this->cam_manager = new cam::Manager(this);
  this->cam_control = new cam::Control(this);
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
  cam_control->set_camera(cam_manager->get_current_camera());

  //---------------------------
}
void Node::loop(){
  //---------------------------

  cam_control->control_mouse();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  gui_panel->run_panel();

  //---------------------------
}
void Node::control(){
  //---------------------------

  //gui_control->run_control();

  //---------------------------
}
void Node::reset(){
  //---------------------------

  cam_manager->reset();

  //---------------------------
}


}
