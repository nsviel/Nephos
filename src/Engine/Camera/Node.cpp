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

  this->utl_window = utl_node->get_utl_window();
  this->cam_manager = new eng::cam::Manager(engine);
  this->cam_control = new eng::cam::Control(this);

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
void Node::reset(){
  //---------------------------

  cam_manager->reset();

  //---------------------------
}


}
