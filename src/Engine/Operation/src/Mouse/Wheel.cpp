#include "Wheel.h"

#include <Engine/Namespace.h>


namespace eng::ope{

//Constructor / Destructor
Wheel::Wheel(eng::ope::Node* node_operation){
  //---------------------------

  eng::Node* node_engine = node_operation->get_node_engine();
  eng::scene::Node* node_scene = node_engine->get_node_scene();
  eng::cam::Node* node_camera = node_engine->get_node_camera();

  this->cam_control = node_camera->get_camera_control();
  this->sce_scene = node_scene->get_scene();
  this->ope_operation = new eng::ope::Operation();

  this->mode = WHEEL_CAM_Z;

  //---------------------------
}
Wheel::~Wheel(){}

//Main function
void Wheel::change_mode(){
  //---------------------------

  this->mode--;
  if(mode == 0) mode = sizeof(Wheel_mode) - 1;

  //---------------------------
}

}
