#include "Node.h"

#include <Engine/Base/Namespace.h>
#include <Engine/Engine.h>
#include <Utility/Namespace.h>
#include <Utility/Element/Namespace.h>


namespace eng::camera{

//Constructor / Destructor
Node::Node(Engine* engine){
  //---------------------------

  this->cam_manager = new eng::camera::Manager(engine);
  this->cam_control = new eng::camera::Control(engine);
  cam_manager->create_camera();

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

  eng::data::Camera* camera = cam_manager->get_camera(0);
  cam_control->set_camera(camera);

  //---------------------------
}
void Node::loop(){
  //---------------------------

  cam_control->control_mouse();

  //---------------------------
}
void Node::reset(){
  //---------------------------

  eng::data::Camera* camera = cam_manager->get_camera(0);
  camera->reset();

  //---------------------------
}


}
