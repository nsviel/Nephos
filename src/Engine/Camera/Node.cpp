#include "Node.h"

#include <Engine/Base/Namespace.h>
#include <Engine/Engine.h>
#include <Utility/Namespace.h>
#include <Utility/Element/Namespace.h>


namespace eng::camera{

//Constructor / Destructor
Node::Node(Engine* engine){
  //---------------------------

  this->camera = new eng::data::Camera();
  this->cam_control = new eng::camera::Control(engine, camera);

  //---------------------------
}
Node::~Node(){
  //---------------------------

  delete camera;
  delete cam_control;

  //---------------------------
}

//Main function
void Node::loop(){
  //---------------------------

  cam_control->control_mouse();

  //---------------------------
}
void Node::reset(){
  //---------------------------

  camera->reset();

  //---------------------------
}


}
