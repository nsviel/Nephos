#include "Node.h"


#include <Engine/Engine.h>
#include <Utility/Namespace.h>
#include <Utility/Element/Namespace.h>


namespace camera::src{

//Constructor / Destructor
Node::Node(Engine* engine){
  //---------------------------

  this->cam_manager = new camera::src::Manager(engine);
  this->cam_control = new camera::src::Control(engine);

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
