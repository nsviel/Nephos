#include "Node.h"

#include <Engine/Engine.h>
#include <Engine/Camera/Namespace.h>
#include <Utility/Namespace.h>
#include <Utility/Element/src/Namespace.h>


namespace eng::cam{

//Constructor / Destructor
Node::Node(Engine* engine){
  //---------------------------

  utl::Node* utl_node = engine->get_node_utility();

  this->engine = engine;
  this->utl_window = utl_node->get_utl_window();
  this->cam_manager = new eng::cam::Manager(this);
  this->cam_control = new eng::cam::Control(this);
  this->gui_control = new eng::cam::gui::Control(this);
  this->gui_panel = new eng::cam::gui::Panel(this, &show_panel);

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
  gui_control->run_control();

  //---------------------------
}
void Node::reset(){
  //---------------------------

  cam_manager->reset();

  //---------------------------
}


}
