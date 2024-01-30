#include "Node.h"

#include <Engine/Node.h>
#include <Engine/Camera/Namespace.h>
#include <Utility/Namespace.h>
#include <Utility/Element/src/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace eng::cam{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  utl::gui::Panel* cam_panel = new_panel("Camera", ICON_FA_CAMERA, false);
  //---------------------------

  utl::Node* node_utility = node_engine->get_node_utility();

  this->node_engine = node_engine;
  this->utl_window = node_utility->get_utl_window();
  this->cam_manager = new eng::cam::Manager(this);
  this->cam_control = new eng::cam::Control(this);
  this->gui_control = new eng::cam::gui::Control(this);
  this->gui_panel = new eng::cam::gui::Panel(this, &cam_panel->is_open);

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

  gui_control->run_control();

  //---------------------------
}
void Node::reset(){
  //---------------------------

  cam_manager->reset();

  //---------------------------
}


}
