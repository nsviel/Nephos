#include "Node.h"

#include <Engine/Base/Namespace.h>
#include <Engine/Engine.h>
#include <Utility/Namespace.h>
#include <Utility/Element/Namespace.h>


namespace eng::camera{

//Constructor / Destructor
Node::Node(Engine* engine){
  //---------------------------

  util::Node* utility = engine->get_utility();
  util::element::Window* utl_window = utility->get_utl_window();

  this->camera = new eng::data::Camera();
  this->cam_arcball = new eng::camera::mode::Arcball(utl_window);
  this->cam_fp = new eng::camera::mode::Player(utl_window);
  this->cam_zoom = new eng::camera::Zoom(utl_window);
  this->cam_proj = new eng::camera::Projection(utl_window);
  this->cam_control = new eng::camera::Control(engine, camera);

  this->arcball_origin = vec3(0, 0, 0);

  //---------------------------
}
Node::~Node(){
  //---------------------------

  delete cam_arcball;
  delete cam_fp;
  delete cam_zoom;
  delete cam_proj;

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
